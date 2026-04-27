// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnCombatComponentBase.h"

#include "GameplayTagContainer.h"
#include "Actor/HeroWeaponBase.h"
#include "Components/BoxComponent.h"
#include "ETC/Define.h"


void UPawnCombatComponentBase::OnHitTargetActor(AActor* HitActor)
{
	
}

void UPawnCombatComponentBase::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

void UPawnCombatComponentBase::RegisterSpawnedWeapon(FGameplayTag InWeaponTag, AHeroWeaponBase* InWeapon, const bool bRegister)
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

void UPawnCombatComponentBase::ToggleWeaponCollision(const bool bEnable)
{
	auto* HeroWeapon = GetCurrentEquippedWeapon();
	VALID_RETURN(HeroWeapon);
	
	if (!bEnable)
	{
		OverlappedActorList.Empty();
	}
	
	ECollisionEnabled::Type CollisionType = bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision;
	
	HeroWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(CollisionType);
}

AHeroWeaponBase* UPawnCombatComponentBase::GetCarriedWeaponByTag(const FGameplayTag InWeaponTag) const
{
	if (const auto FoundWeapon = CharacterWeaponMap.Find(InWeaponTag))
	{
		return *FoundWeapon;
	}
	
	return nullptr;
}

AHeroWeaponBase* UPawnCombatComponentBase::GetCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
