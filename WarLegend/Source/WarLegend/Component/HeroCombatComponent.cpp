// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCombatComponent.h"

#include "Actor/HeroWeaponBase.h"
#include "ETC/Define.h"


void UHeroCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTag, AHeroWeaponBase* InWeapon, const bool bRegister)
{
	VALID_RETURN(InWeaponTag);
	CharacterWeaponMap.Emplace(InWeaponTag,InWeapon);

	if (!bRegister)
	{
		return;
	}
	
	CurrentEquippedWeaponTag = InWeaponTag;
}

AHeroWeaponBase* UHeroCombatComponent::GetCharacterCarriedWeaponByTag(const FGameplayTag InWeaponTag) const
{
	if (const auto FoundWeapon = CharacterWeaponMap.Find(InWeaponTag))
	{
		return *FoundWeapon;
	}
	
	return nullptr;
}

AHeroWeaponBase* UHeroCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
