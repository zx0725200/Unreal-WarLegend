// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonAbilityConfigBase.h"
#include "EnemyAbilityConfig.generated.h"

class UEnemyAbility;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UEnemyAbilityConfig : public UCommonAbilityConfigBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilityToComponent(UHeroAbilitySystemComponent* InAbilityComponent) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	TArray<TSubclassOf<UEnemyAbility>> EnemyAbilityList;
};
