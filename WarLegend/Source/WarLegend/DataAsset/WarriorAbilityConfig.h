// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonAbilityConfigBase.h"
#include "GameplayTagContainer.h"
#include "WarriorAbilityConfig.generated.h"

class UHeroAbility;

USTRUCT(BlueprintType)
struct FWarriorAbilityStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Battle"))
	FGameplayTag AbilityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHeroAbility> WarriorAbility;

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class WARLEGEND_API UWarriorAbilityConfig : public UCommonAbilityConfigBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilityToComponent(UHeroAbilitySystemComponent* InAbilityComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Ability", meta = (TitleProperty = "AbilityTag"))
	TArray<FWarriorAbilityStruct> WarriorAbilityList;
};
