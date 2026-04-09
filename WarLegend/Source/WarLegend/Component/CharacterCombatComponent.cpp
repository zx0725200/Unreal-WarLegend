// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCombatComponent.h"

#include "Actor/CharWeapon.h"


ACharWeaponBase* UCharacterCombatComponent::GetCharWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ACharWeaponBase>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
