// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCombatComponent.h"

#include "Actor/CharWeaponBase.h"
#include "ETC/Define.h"


void UHeroCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTag, ACharWeaponBase* InWeapon, const bool bRegister)
{
	VALID_RETURN(InWeaponTag);
	CharacterWeaponMap.Emplace(InWeaponTag,InWeapon);

	if (!bRegister)
	{
		return;
	}
	
	CurrentEquippedWeaponTag = InWeaponTag;
}

ACharWeaponBase* UHeroCombatComponent::GetCharacterCarriedWeaponByTag(const FGameplayTag InWeaponTag) const
{
	if (CharacterWeaponMap.Contains(InWeaponTag))
	{
		if (const auto FoundWeapon = CharacterWeaponMap.Find(InWeaponTag))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

ACharWeaponBase* UHeroCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
