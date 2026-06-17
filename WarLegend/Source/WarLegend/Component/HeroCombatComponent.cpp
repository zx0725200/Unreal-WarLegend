// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/HeroWeaponBase.h"
#include "ETC/Define.h"
#include "ETC/GamePlayTag.h"


UHeroCombatComponent::UHeroCombatComponent()
{
	
}

void UHeroCombatComponent::OnHitTargetActor(AActor* InHitActor, const FHitResult& InHitResult)
{
	if (OverlappedActorList.Contains(InHitActor))
	{
		return;
	}
	
	OverlappedActorList.AddUnique(InHitActor);
	
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	VALID_RETURN(OwningPawn);
	
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwningPawn);
	VALID_RETURN(AbilitySystemComponent);
	
	// ? 접점이 살짝 낮게 느껴져서 이펙트를 위로 올림.
	FHitResult HitForCue = InHitResult;
	HitForCue.ImpactPoint.Z += 50.f;
	HitForCue.Location.Z += 50.f;
	
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddHitResult(HitForCue);
	
	FGameplayEventData Data;
	Data.Instigator = OwningPawn;
	Data.Target = InHitActor;
	Data.ContextHandle = ContextHandle;

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
