// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_HeroHitReact.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ETC/GamePlayTag.h"

UGA_HeroHitReact::UGA_HeroHitReact()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;

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
				/*StopWhenAbilityEnds*/ false, 1.f);

		PlayTask->ReadyForActivation();
	}

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

	// HitReacting 태그는 ActivationOwnedTags 라 GAS 가 종료 시 자동으로 제거한다.
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
