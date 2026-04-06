// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharDataConfigBase.h"
#include "GameplayTagContainer.h"
#include "WarriorDataConfig.generated.h"

class UWarriorAbility;

USTRUCT(BlueprintType)
struct FWarriorAbilityStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Battle"))
	FGameplayTag AbilityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarriorAbility> WarriorAbility;

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class WARLEGEND_API UWarriorDataConfig : public UCharDataConfigBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UCharAbilitySystemComponent* InAbilityComponent, const int32 InApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Ability", meta = (TitleProperty = "AbilityTag"))
	TArray<FWarriorAbilityStruct> WarriorAbilityList;
};
