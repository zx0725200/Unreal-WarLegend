// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "WarLegendBaseCharacter.generated.h"

class UCommonAbilityConfigBase;
class UHeroAttributeSet;
class UHeroAbilitySystemComponent;

UCLASS()
class WARLEGEND_API AWarLegendBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWarLegendBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UHeroAbilitySystemComponent* GetWarriorAbilitySystemComponent() const { return CharAbilitySystemComponent; }
	UHeroAttributeSet* GetWarriorAttributeSet() const { return CharAttributeSet; }
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHeroAbilitySystemComponent> CharAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHeroAttributeSet> CharAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharData")
	TSoftObjectPtr<UCommonAbilityConfigBase> CharDataConfig;
};
