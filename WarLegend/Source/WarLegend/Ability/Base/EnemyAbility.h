// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonAbilityBase.h"
#include "EnemyAbility.generated.h"

class UEnemyCombatComponent;
class AEnemyCharacter;

/**
 * 
 */
UCLASS()
class WARLEGEND_API UEnemyAbility : public UCommonAbilityBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Enemy|Ability")
	AEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Enemy|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AEnemyCharacter> CachedEnemyCharacter;
};
