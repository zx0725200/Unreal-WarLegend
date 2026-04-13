// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonAbilityBase.h"
#include "HeroAbility.generated.h"

class AWarLegendPlayerController;
class AWarLegendCharacter;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UHeroAbility : public UCommonAbilityBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	AWarLegendCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	AWarLegendPlayerController* GetHeroControllerFromActorInfo();

private:
	TWeakObjectPtr<AWarLegendCharacter> HeroCharacter;
	TWeakObjectPtr<AWarLegendPlayerController> HeroController;
};
