// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/CharplayAbility.h"

#include "AbilitySystemComponent.h"

void UCharplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	if (ActorInfo == nullptr || Spec.IsActive())
	{
		return;
	}
	
	if (AbilityActivation == ECharAbilityActivation::OnTriggered)
	{
		return;
	}
	
	ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
}

void UCharplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	if (ActorInfo == nullptr )
	{
		return;
	}
	
	if (AbilityActivation == ECharAbilityActivation::OnTriggered)
	{
		return;
	}
	
	ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
}
