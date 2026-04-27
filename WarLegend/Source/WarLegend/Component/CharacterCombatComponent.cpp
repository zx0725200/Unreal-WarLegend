// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCombatComponent.h"

#include "Actor/HeroWeapon.h"


AHeroWeaponBase* UCharacterCombatComponent::GetCharWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AHeroWeaponBase>(GetHeroCarriedWeaponByTag(InWeaponTag));
}
