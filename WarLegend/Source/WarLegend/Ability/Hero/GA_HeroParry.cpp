#include "GA_HeroParry.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ETC/Define.h"
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
	
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(ParryTimer, this, &UGA_HeroParry::CloseParryWindow,ParryDuration, /*bLoop*/ false);
	}

	VALID_RETURN(ParryMontage);
	
	UAbilityTask_PlayMontageAndWait* PlayTask =UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, ParryMontage,
				1.f, NAME_None,
				true, 1.f);

	PlayTask->OnCompleted.AddDynamic(this, &UGA_HeroParry::OnMontageFinished);
	PlayTask->OnBlendOut.AddDynamic(this, &UGA_HeroParry::OnMontageFinished);
	PlayTask->OnInterrupted.AddDynamic(this, &UGA_HeroParry::OnMontageFinished);
	PlayTask->OnCancelled.AddDynamic(this, &UGA_HeroParry::OnMontageFinished);
	PlayTask->ReadyForActivation();
}

void UGA_HeroParry::OnMontageFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,true, false);
}

void UGA_HeroParry::CloseParryWindow()
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		ASC->RemoveLooseGameplayTag(GamePlayTag::Player_State_Parrying);
	}
	
	if (!ParryMontage)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

void UGA_HeroParry::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	// ? 어떤 경로로 끝나든 윈도우 타이머/상태 태그를 정리한다.
	// ? Super::EndAbility는 어빌리티의 최종단계라서 마지막에 하는게 좋다.
	// ? GAS에서는 CleanUp -> Super순서가 관용.
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ParryTimer);
	}
	
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		ASC->RemoveLooseGameplayTag(GamePlayTag::Player_State_Parrying);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
