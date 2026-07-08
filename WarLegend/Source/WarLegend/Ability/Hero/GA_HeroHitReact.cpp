// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_HeroHitReact.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Character/WarLegendCharacter.h"
#include "Controller/WarLegendPlayerController.h"
#include "ETC/GamePlayTag.h"

UGA_HeroHitReact::UGA_HeroHitReact()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	// 피격 이벤트는 서버(GA_BossAttack)에서만 발생하지만, 피격 몽타주는 소유 클라이언트에서도
	// 보여야 한다. 소유 히어로는 autonomous proxy라 서버가 재생한 몽타주가 복제되지 않으므로
	// (GAS가 예측 재생을 가정), ServerOnly면 클라 화면엔 안 뜬다.
	// ServerInitiated: 서버가 발동시키고 활성화를 소유 클라로 복제 → 클라가 몽타주를 로컬 재생.
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

	// 이미 피격 중에 또 맞으면 다시 발동되어 경직이 갱신되게.
	bRetriggerInstancedAbility = true;

	// Shared.Event.PlayerHit 이벤트가 오면 자동 발동.
	FAbilityTriggerData Trigger;
	Trigger.TriggerTag = GamePlayTag::Shared_Event_PlayerHit;
	Trigger.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(Trigger);

	// 발동~종료 동안 소유자에게 이 태그가 붙는다. 공격/구르기 어빌리티가 이 태그를
	// ActivationBlockedTags 로 막으면 경직 시간 동안 행동이 불가능해진다.
	ActivationOwnedTags.AddTag(GamePlayTag::Player_State_HitReacting);

	// 맞는 순간 진행 중이던 공격을 끊는다. 구르기 등 다른 액션은 이 태그 목록에 BP 에서 추가.
	CancelAbilitiesWithTag.AddTag(GamePlayTag::Player_Ability_Attack_Light_Axe);
}

void UGA_HeroHitReact::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	// 피격 애니 재생. StopWhenAbilityEnds=false 라 경직이 풀려도 몽타주를 자르지 않아
	// 자연스럽게 idle 로 블렌드된다.
	if (HitReactMontage)
	{
		UAbilityTask_PlayMontageAndWait* PlayTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, HitReactMontage,
				/*PlayRate*/ 1.f, NAME_None,
				/*StopWhenAbilityEnds*/ false,
				/*AnimRootMotionTranslationScale*/ 0.f);  // 루트모션 이동 제거 → 제자리 고정

		PlayTask->ReadyForActivation();
	}

	// 스턴 동안 이동/회전 입력 차단(어빌리티는 HitReacting 태그로 이미 차단).
	SetHeroInputLocked(true);

	// 행동 불가 시간의 '권한'은 HitStunDuration 타이머. 이 시간 동안 HitReacting 태그가 유지되어
	// 공격/구르기가 막히고, 끝나면 종료되어 태그가 풀린다.
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			StunTimer, this, &UGA_HeroHitReact::OnStunFinished, FMath::Max(HitStunDuration, 0.01f), /*bLoop*/ false);
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, /*Replicate*/ true, /*Cancel*/ false);
	}
}

void UGA_HeroHitReact::OnStunFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, /*Replicate*/ true, /*Cancel*/ false);
}

void UGA_HeroHitReact::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(StunTimer);
	}

	// 스턴 종료 → 이동/회전 입력 잠금 해제(행동 재개).
	SetHeroInputLocked(false);

	// HitReacting 태그는 ActivationOwnedTags 라 GAS 가 종료 시 자동으로 제거한다.
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_HeroHitReact::SetHeroInputLocked(bool bLocked)
{
	// 이미 같은 상태면 무시. 이렇게 인스턴스당 잠금/해제를 각 1회로 보장해야
	// SetIgnoreMoveInput 의 내부 카운터가 어긋나 영구 잠김이 되는 것을 막을 수 있다.
	// (ServerInitiated + bRetriggerInstancedAbility 로 Activate/End 가 중복 호출될 수 있음.)
	if (bLocked == bInputLocked)
	{
		return;
	}
	bInputLocked = bLocked;

	// 이동/회전 입력 차단·해제. AddMovementInput/AddControllerInput 이 이 플래그를 확인하므로
	// 입력 바인딩이 컨트롤러/폰 어디에 있든 확실히 막힌다.
	if (AWarLegendPlayerController* PC = GetHeroControllerFromActorInfo())
	{
		PC->SetIgnoreMoveInput(bLocked);
		PC->SetIgnoreLookInput(bLocked);
	}

	// 잠글 때 현재 이동 관성을 끊는다(이동모드는 건드리지 않음 → 넷 desync 로 복구 실패 방지).
	// 루트모션 넉백은 몽타주 태스크의 RootMotionTranslationScale=0 으로 이미 제거됨.
	if (bLocked)
	{
		if (AWarLegendCharacter* Hero = GetHeroCharacterFromActorInfo())
		{
			if (UCharacterMovementComponent* MoveComp = Hero->GetCharacterMovement())
			{
				MoveComp->StopMovementImmediately();
			}
		}
	}
}
