// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BossAttack.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UGA_BossAttack::UGA_BossAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UGA_BossAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	// 쿨타임/코스트 커밋. CooldownGameplayEffectClass가 있으면 자동 부여됨.
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, /*Replicate*/ true, /*Cancel*/ true);
		return;
	}

	if (!AttackMontage)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 몽타주 재생
	UAbilityTask_PlayMontageAndWait* PlayTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, AttackMontage,
			/*PlayRate*/ 1.f, NAME_None,
			/*StopWhenAbilityEnds*/ true, 1.f);

	PlayTask->OnCompleted.AddDynamic(this, &UGA_BossAttack::OnMontageCompleted);
	PlayTask->OnBlendOut.AddDynamic(this, &UGA_BossAttack::OnMontageCompleted);
	PlayTask->OnInterrupted.AddDynamic(this, &UGA_BossAttack::OnMontageInterrupted);
	PlayTask->OnCancelled.AddDynamic(this, &UGA_BossAttack::OnMontageInterrupted);
	PlayTask->ReadyForActivation();

	// 몽타주 AnimNotify가 쏘는 히트 이벤트 대기
	if (HitEventTag.IsValid())
	{
		UAbilityTask_WaitGameplayEvent* WaitTask =
			UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
				this, HitEventTag,
				/*OptionalExternalTarget*/ nullptr,
				/*OnlyTriggerOnce*/ false,
				/*OnlyMatchExact*/ false);

		WaitTask->EventReceived.AddDynamic(this, &UGA_BossAttack::OnHitEventReceived);
		WaitTask->ReadyForActivation();
	}
}

void UGA_BossAttack::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
			   /*Replicate*/ true, /*Cancel*/ false);
}

void UGA_BossAttack::OnMontageInterrupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
			   /*Replicate*/ true, /*Cancel*/ true);
}

void UGA_BossAttack::OnHitEventReceived(FGameplayEventData Payload)
{
	AActor* Target = const_cast<AActor*>(Payload.Target.Get());
	UAbilitySystemComponent* TargetASC =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();

	if (!TargetASC || !SourceASC || !DamageEffectClass) return;

	// Payload에 HitResult 있으면 그대로 사용 (GameplayCue VFX 위치용)
	FHitResult Hit;
	if (const FHitResult* P = Payload.ContextHandle.GetHitResult())
	{
		Hit = *P;
	}

	FGameplayEffectSpecHandle Spec = MakeDamageSpec(Hit);
	if (Spec.IsValid())
	{
		SourceASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), TargetASC);
	}
}

FGameplayEffectSpecHandle UGA_BossAttack::MakeDamageSpec(const FHitResult& Hit) const
{
	const UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo_Ensured();

	FGameplayEffectContextHandle Ctx = ASC->MakeEffectContext();
	Ctx.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	Ctx.AddHitResult(Hit);

	FGameplayEffectSpecHandle Spec =
		ASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), Ctx);
	if (!Spec.IsValid()) return Spec;

	for (const TPair<FGameplayTag, float>& Pair : SetByCallerMagnitudes)
	{
		Spec.Data->SetSetByCallerMagnitude(Pair.Key, Pair.Value);
	}
	return Spec;
}
