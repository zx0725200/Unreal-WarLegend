// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCombatComponent.h"

#include "Actor/HeroWeaponBase.h"
#include "Components/BoxComponent.h"
#include "ETC/Define.h"


void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

void UHeroCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTag, AHeroWeaponBase* InWeapon, const bool bRegister)
{
	VALID_RETURN(InWeaponTag);
	CharacterWeaponMap.Emplace(InWeaponTag,InWeapon);

	InWeapon->OnWeaponHitTarget.BindUObject(this,&ThisClass::OnHitTargetActor);
	InWeapon->OnWeaponPulledFromTarget.BindUObject(this,&ThisClass::OnWeaponPulledFromTargetActor);
	
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

void UHeroCombatComponent::ToggleWeaponCollision(const bool bEnable)
{
	auto* HeroWeapon = GetCharacterCurrentEquippedWeapon();
	VALID_RETURN(HeroWeapon);
	
	ECollisionEnabled::Type CollisionType = bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision;
	
	HeroWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(CollisionType);
}
