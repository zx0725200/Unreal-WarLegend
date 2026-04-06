// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponentBase.h"
#include "CharCombatComponent.generated.h"


class ACharWeaponBase;
struct FGameplayTag;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARLEGEND_API UCharCombatComponent : public UPawnCombatComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTag, ACharWeaponBase* InWeapon, const bool bRegister = false);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	ACharWeaponBase* GetCharacterCarriedWeaponByTag(const FGameplayTag InWeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	ACharWeaponBase* GetCharacterCurrentEquippedWeapon() const;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Char|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<ACharWeaponBase>> CharacterWeaponMap;
};
