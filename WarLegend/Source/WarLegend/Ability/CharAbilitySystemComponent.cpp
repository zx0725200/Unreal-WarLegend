// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/CharAbilitySystemComponent.h"

void UCharAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UCharAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}
