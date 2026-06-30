// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BossStagger.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ETC/GamePlayTag.h"

UGA_BossStagger::UGA_BossStagger()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;

	// Shared.Event.BossStagger 이벤트가 오면 자동 발동.
	FAbilityTriggerData Trigger;
	Trigger.TriggerTag = GamePlayTag::Shared_Event_BossStagger;
	Trigger.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(Trigger);

	// 발동 시 진행 중이던 보스 공격을 끊는다(= 하던 모션 정지). 자식 태그까지 매칭됨.
	CancelAbilitiesWithTag.AddTag(GamePlayTag::Enemy_Ability_Attack_NormalA);
	CancelAbilitiesWithTag.AddTag(GamePlayTag::Enemy_Ability_Attack_NormalB);
	CancelAbilitiesWithTag.AddTag(GamePlayTag::Enemy_Ability_Attack_Magic);
	CancelAbilitiesWithTag.AddTag(GamePlayTag::Enemy_Ability_Attack_Combo);

	// 타격 큐와 동일한 GameplayCue 시스템 사용. 패링은 데미지 GE 가 없어 직접 ExecuteGameplayCue 한다.
	ParryCueTag = GamePlayTag::GamePlayCue_Parry;
}

void UGA_BossStagger::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	AActor* Boss = GetAvatarActorFromActorInfo();
	if (!ASC || !Boss)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, /*Replicate*/ true, /*Cancel*/ true);
		return;
	}

	// 그로기 상태 ON. 종료 시 EndAbility 에서 제거.
	ASC->AddLooseGameplayTag(GamePlayTag::Enemy_State_Groggy);

	// 패링 성공 연출을 GameplayCue 로 발동(이펙트/사운드는 GameplayCueNotify 가 처리, 서버→클라 복제됨).
	if (ParryCueTag.IsValid())
	{
		FGameplayCueParameters CueParams;
		CueParams.Instigator = Boss;
		// 충돌 위치가 있으면 그 지점, 없으면 보스 위치에 큐를 띄운다.
		if (TriggerEventData && TriggerEventData->ContextHandle.GetHitResult())
		{
			CueParams.Location = TriggerEventData->ContextHandle.GetHitResult()->ImpactPoint;
		}
		else
		{
			CueParams.Location = Boss->GetActorLocation();
		}

		ASC->ExecuteGameplayCue(ParryCueTag, CueParams);
	}

	bMontageEnded = false;
	bGroggyElapsed = false;

	// 그로기 모션 재생. StopWhenAbilityEnds=false 라 어빌리티가 끝나도 몽타주를 잘라내지 않는다.
	// → 몽타주가 끝까지 재생되며 몽타주 자체의 Blend Out 설정으로 idle 에 부드럽게 복귀.
	if (StaggerMontage)
	{
		UAbilityTask_PlayMontageAndWait* PlayTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, StaggerMontage,
				/*PlayRate*/ 1.f, NAME_None,
				/*StopWhenAbilityEnds*/ false, 1.f);

		// 블렌드아웃이 시작되면(= 자연스러운 idle 복귀 시작) 몽타주는 끝난 것으로 본다.
		PlayTask->OnCompleted.AddDynamic(this, &UGA_BossStagger::OnStaggerMontageEnded);
		PlayTask->OnBlendOut.AddDynamic(this, &UGA_BossStagger::OnStaggerMontageEnded);
		PlayTask->OnInterrupted.AddDynamic(this, &UGA_BossStagger::OnStaggerMontageEnded);
		PlayTask->OnCancelled.AddDynamic(this, &UGA_BossStagger::OnStaggerMontageEnded);
		PlayTask->ReadyForActivation();
	}
	else
	{
		// 모션이 없으면 GroggyDuration 만으로 종료 타이밍 결정.
		bMontageEnded = true;
	}

	// 경직(공격 금지) 최소 보장 시간. 실제 종료는 '몽타주 끝'과 'GroggyDuration' 중 늦은 쪽.
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			GroggyTimer, this, &UGA_BossStagger::OnGroggyTimerElapsed, FMath::Max(GroggyDuration, 0.01f), /*bLoop*/ false);
	}
	else
	{
		bGroggyElapsed = true;
		TryFinish();
	}
}

void UGA_BossStagger::OnGroggyTimerElapsed()
{
	bGroggyElapsed = true;
	TryFinish();
}

void UGA_BossStagger::OnStaggerMontageEnded()
{
	bMontageEnded = true;
	TryFinish();
}

void UGA_BossStagger::TryFinish()
{
	// 둘 다 충족돼야 종료. 몽타주를 끝까지 재생하면서도 최소 경직 시간을 보장한다.
	if (bMontageEnded && bGroggyElapsed)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, /*Replicate*/ true, /*Cancel*/ false);
	}
}

void UGA_BossStagger::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(GroggyTimer);
	}

	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		ASC->RemoveLooseGameplayTag(GamePlayTag::Enemy_State_Groggy);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
