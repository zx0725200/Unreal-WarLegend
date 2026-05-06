// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnCombatComponentBase.h"

#include "GameplayTagContainer.h"
#include "Actor/HeroWeaponBase.h"
#include "Components/BoxComponent.h"
#include "ETC/Define.h"


void UPawnCombatComponentBase::OnHitTargetActor(AActor* HitActor, const FHitResult& InHitResult)
{
	
}

void UPawnCombatComponentBase::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

// BP에서 무기 스폰 후 직접 호출 - bRegister=true면 현재 장착 무기로 즉시 등록
void UPawnCombatComponentBase::RegisterSpawnedWeapon(FGameplayTag InWeaponTag, AHeroWeaponBase* InWeapon, const bool bRegister)
{
	VALID_RETURN(InWeaponTag);
	CharacterWeaponMap.Emplace(InWeaponTag,InWeapon);

	InWeapon->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeapon->OnWeaponPulledFromTarget.BindUObject(this,&ThisClass::OnWeaponPulledFromTargetActor);
	
	if (!bRegister)
	{
		return;
	}
	
	CurrentEquippedWeaponTag = InWeaponTag;
}

void UPawnCombatComponentBase::ToggleWeaponCollision(const ECollisionEnabled::Type InCollisionType)
{
	auto* HeroWeapon = GetCurrentEquippedWeapon();
	VALID_RETURN(HeroWeapon);
	
	const bool bUnEquip = InCollisionType == ECollisionEnabled::NoCollision;
	if (bUnEquip)
	{
		OverlappedActorList.Empty();
	}
	
	HeroWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(InCollisionType);
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
