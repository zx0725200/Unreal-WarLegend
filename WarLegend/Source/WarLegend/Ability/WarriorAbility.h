// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharAbilityBase.h"
#include "WarriorAbility.generated.h"

class AWarLegendPlayerController;
class AWarLegendCharacter;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UWarriorAbility : public UCharAbilityBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarLegendCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarLegendPlayerController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UCharCombatComponent* GetHeroCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AWarLegendCharacter> CachedWarriorHeroCharacter;
	TWeakObjectPtr<AWarLegendPlayerController> CachedWarriorHeroController;
};
