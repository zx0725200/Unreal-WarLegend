// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CommonAbilityConfigBase.generated.h"

class UGameplayEffect;
enum class EAbilityGiveMode : uint8;
class UGameplayAbility;
class UHeroAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UCommonAbilityConfigBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilityToComponent(UHeroAbilitySystemComponent* InAbilityComponent);

private:
	void Internal_GiveAbility(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities, UHeroAbilitySystemComponent* InAbilityComponent, EAbilityGiveMode InMode);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "HeroData")
	TArray<TSubclassOf<UGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "HeroData")
	TArray<TSubclassOf<UGameplayAbility>> ReactiveAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "HeroData")
	TArray<TSubclassOf<UGameplayEffect>> HeroGamePlayEffects;
};
