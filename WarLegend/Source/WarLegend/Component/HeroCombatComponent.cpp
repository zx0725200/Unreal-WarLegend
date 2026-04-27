// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Actor/HeroWeapon.h"
#include "Actor/HeroWeaponBase.h"
#include "ETC/GamePlayTag.h"


UHeroCombatComponent::UHeroCombatComponent()
{
	UE_LOG(LogTemp,Warning,TEXT("Test Gener"));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* InHitActor)
{
	if (OverlappedActorList.Contains(InHitActor))
	{
		return;
	}
	
	OverlappedActorList.AddUnique(InHitActor);
	
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (!OwningPawn)
	{
		return;
	}
	
	FGameplayEventData Data;
	Data.Instigator = OwningPawn;
	Data.Target = InHitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		OwningPawn,
		GamePlayTag::Shared_Event_MeleeHit,
		Data
	);
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InInteractedActor)
{
}

AHeroWeaponBase* UHeroCombatComponent::GetHeroCarriedWeaponByTag(const FGameplayTag InWeaponTag) const
{
	return Cast<AHeroWeaponBase>(GetCarriedWeaponByTag(InWeaponTag));
}

AHeroWeaponBase* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AHeroWeaponBase>(GetCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroDamage() const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(1);
}
