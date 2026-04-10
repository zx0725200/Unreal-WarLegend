// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/HeroAbilitySystemComponent.h"
#include "Ability/HeroAbility.h"
#include "ETC/Define.h"
#include "ETC/Struct.h"

void UHeroAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	VALID_RETURN(InInputTag);
	
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

void UHeroAbilitySystemComponent::GiveWeaponAbilities(const TArray<FHeroAbilitySet>& InWeaponAbilities, TArray<FGameplayAbilitySpecHandle>& OutAbilityHandles)
{
	if (InWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FHeroAbilitySet& AbilitySet : InWeaponAbilities)
	{
		if(!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.BattleTag);
		
		OutAbilityHandles.Add(GiveAbility(AbilitySpec));
	}
}

void UHeroAbilitySystemComponent::RemoveWeaponAbilities(TArray<FGameplayAbilitySpecHandle>& RemoveHandle)
{
	if (RemoveHandle.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : RemoveHandle)
	{
		ClearAbility(SpecHandle);
	}

	RemoveHandle.Empty();
}
