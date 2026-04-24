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
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTag, AHeroWeaponBase* InWeapon, const bool bRegister = false);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AHeroWeaponBase* GetCharacterCarriedWeaponByTag(const FGameplayTag InWeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AHeroWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void ToggleWeaponCollision(const bool bEnable);

public:
	UPROPERTY(BlueprintReadWrite, Category = "Char|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<AHeroWeaponBase>> CharacterWeaponMap;
};
