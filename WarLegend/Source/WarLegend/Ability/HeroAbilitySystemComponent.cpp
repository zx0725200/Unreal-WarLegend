// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/HeroAbilitySystemComponent.h"
#include "Base/HeroAbility.h"
#include "ETC/Struct.h"

void UHeroAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	const TArray<FGameplayAbilitySpec>& ActivateAbilityList = GetActivatableAbilities();
	if (ActivateAbilityList.IsEmpty())
	{
		return;
	}
	
	for (const FGameplayAbilitySpec& AbilitySpec : ActivateAbilityList)
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

void UHeroAbilitySystemComponent::GiveWeaponAbilities(const TArray<FHeroAbilitySet>& InWeaponAbilityList, TArray<FGameplayAbilitySpecHandle>& OutAbilityHandleList)
{
	if (InWeaponAbilityList.IsEmpty())
	{
		return;
	}

	for (const FHeroAbilitySet& AbilitySet : InWeaponAbilityList)
	{
		if(!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.BattleTag);
		
		FGameplayAbilitySpecHandle AbilitySpecHandle = GiveAbility(AbilitySpec);
		OutAbilityHandleList.Add(AbilitySpecHandle);
	}
}

void UHeroAbilitySystemComponent::RemoveWeaponAbilities(TArray<FGameplayAbilitySpecHandle>& RemoveHandleList)
{
	if (RemoveHandleList.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : RemoveHandleList)
	{
		ClearAbility(SpecHandle);
	}

	RemoveHandleList.Empty();
}
