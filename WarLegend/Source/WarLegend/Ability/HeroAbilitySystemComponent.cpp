// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/HeroAbilitySystemComponent.h"
#include "Ability/HeroAbility.h"
#include "ETC/Struct.h"

void UHeroAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag))
		{
			continue;
		}

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UHeroAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

void UHeroAbilitySystemComponent::GiveWeaponAbilities(
	const TArray<FWarriorHeroAbilitySet>& InWeaponAbilities, int32 ApplyLevel,
	TArray<FGameplayAbilitySpecHandle>& OutAbilityHandles)
{
	if (InWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FWarriorHeroAbilitySet& AbilitySet : InWeaponAbilities)
	{
		if(!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.BattleTag);
		
		OutAbilityHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UHeroAbilitySystemComponent::RemoveWeaponAbilities(TArray<FGameplayAbilitySpecHandle>& InRemoveHandle)
{
	if (InRemoveHandle.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InRemoveHandle)
	{
		if (!SpecHandle.IsValid())
		{
			continue;
		}
		
		ClearAbility(SpecHandle);
	}

	InRemoveHandle.Empty();
}
