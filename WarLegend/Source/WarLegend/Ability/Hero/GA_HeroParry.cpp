// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_HeroParry.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ETC/GamePlayTag.h"

UGA_HeroParry::UGA_HeroParry()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UGA_HeroParry::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	// 쿨타임/코스트 커밋. CooldownGameplayEffectClass가 설정돼 있으면 패링 연타 방지 역할도 한다.
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, /*Replicate*/ true, /*Cancel*/ true);
		return;
	}

	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 패링 윈도우 ON: 이 태그가 붙어있는 동안 보스 타격이 무효화된다.
	ASC->AddLooseGameplayTag(GamePlayTag::Player_State_Parrying);

	// ParryWindowDuration 후 윈도우 닫기.
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			ParryWindowTimer, this, &UGA_HeroParry::CloseParryWindow,
			ParryWindowDuration, /*bLoop*/ false);
	}

	// 패링 모션 재생(선택). 모션이 끝나면 어빌리티 종료.
	if (ParryMontage)
	{
		UAbilityTask_PlayMontageAndWait* PlayTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, ParryMontage,
				/*PlayRate*/ 1.f, NAME_None,
				/*StopWhenAbilityEnds*/ true, 1.f);

		PlayTask->OnCompleted.AddDynamic(this, &UGA_HeroParry::OnMontageFinished);
		PlayTask->OnBlendOut.AddDynamic(this, &UGA_HeroParry::OnMontageFinished);
		PlayTask->OnInterrupted.AddDynamic(this, &UGA_HeroParry::OnMontageFinished);
		PlayTask->OnCancelled.AddDynamic(this, &UGA_HeroParry::OnMontageFinished);
		PlayTask->ReadyForActivation();
	}
	// 모션이 없으면 CloseParryWindow(타이머)가 어빌리티를 종료한다.
}

void UGA_HeroParry::OnMontageFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
			   /*Replicate*/ true, /*Cancel*/ false);
}

void UGA_HeroParry::CloseParryWindow()
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		ASC->RemoveLooseGameplayTag(GamePlayTag::Player_State_Parrying);
	}

	// 모션이 없으면 윈도우가 닫히는 시점에 어빌리티를 종료한다.
	// (모션이 있으면 OnMontageFinished 에서 종료)
	if (!ParryMontage)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

void UGA_HeroParry::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	// 어떤 경로로 끝나든 윈도우 타이머/상태 태그를 정리한다(중복 제거는 안전).
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ParryWindowTimer);
	}

	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		ASC->RemoveLooseGameplayTag(GamePlayTag::Player_State_Parrying);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
