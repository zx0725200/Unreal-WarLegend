// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonAbilityConfigBase.h"
#include "HeroAbilityConfig.generated.h"

struct FHeroAbilitySet;
class UHeroAbility;

/**
 * 
 */
UCLASS()
class WARLEGEND_API UHeroAbilityConfig : public UCommonAbilityConfigBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilityToComponent(UHeroAbilitySystemComponent* InAbilityComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Ability", meta = (TitleProperty = "BattleTag"))
	TArray<FHeroAbilitySet> WarriorAbilityList;
};
