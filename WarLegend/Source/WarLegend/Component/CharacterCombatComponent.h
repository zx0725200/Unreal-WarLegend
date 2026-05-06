// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroCombatComponent.h"
#include "CharacterCombatComponent.generated.h"


class AHeroWeaponBase;
struct FGameplayTag;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARLEGEND_API UCharacterCombatComponent : public UHeroCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Hero|Combat")
	AHeroWeaponBase* GetCharWeaponByTag(FGameplayTag InWeaponTag) const;
};
