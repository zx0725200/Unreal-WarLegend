// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ETC/HeroCombatInterface.h"
#include "GameFramework/Character.h"
#include "WarLegendBaseCharacter.generated.h"

class UCommonAbilityConfigBase;
class UHeroAttributeSet;
class UHeroAbilitySystemComponent;

UCLASS()
class WARLEGEND_API AWarLegendBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IHeroCombatInterface
{
	GENERATED_BODY()

public:
	AWarLegendBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UPawnCombatComponentBase* GetPawnCombatComponent() const override;
	
	UHeroAbilitySystemComponent* GetWarriorAbilitySystemComponent() const { return HeroAbilitySystemComponent; }
	UHeroAttributeSet* GetWarriorAttributeSet() const { return HeroAttributeSet; }
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHeroAbilitySystemComponent> HeroAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHeroAttributeSet> HeroAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TSoftObjectPtr<UCommonAbilityConfigBase> DataConfig;
};
