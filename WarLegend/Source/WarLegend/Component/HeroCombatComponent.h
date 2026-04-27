// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponentBase.h"
#include "HeroCombatComponent.generated.h"


class AHeroWeaponBase;
struct FGameplayTag;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARLEGEND_API UHeroCombatComponent : public UPawnCombatComponentBase
{
	GENERATED_BODY()
	
public:
	UHeroCombatComponent();
	
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
	
	UFUNCTION(BlueprintCallable, Category = "Hero|Combat")
	AHeroWeaponBase* GetHeroCarriedWeaponByTag(const FGameplayTag InWeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Hero|Combat")
	AHeroWeaponBase* GetHeroCurrentEquippedWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category = "Hero|Combat")
	float GetHeroDamage() const;
};
