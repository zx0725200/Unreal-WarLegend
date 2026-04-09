// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharCombatComponent.h"
#include "CharacterCombatComponent.generated.h"


class ACharWeaponBase;
struct FGameplayTag;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARLEGEND_API UCharacterCombatComponent : public UCharCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	ACharWeaponBase* GetCharWeaponByTag(FGameplayTag InWeaponTag) const;
};
