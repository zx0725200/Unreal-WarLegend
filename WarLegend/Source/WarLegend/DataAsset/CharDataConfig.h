// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharDataConfig.generated.h"

class UGameplayAbility;
class UCharAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UCharDataConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UCharAbilitySystemComponent* InAbilityComponent, const int32 InApplyLevel = 1);

protected:
	void GiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities, UCharAbilitySystemComponent* InAbilityComponent, const int32 InApplyLevel = 1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "CharData")
	TArray<TSubclassOf<UGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "CharData")
	TArray<TSubclassOf<UGameplayAbility>> ReactiveAbilities;
};
