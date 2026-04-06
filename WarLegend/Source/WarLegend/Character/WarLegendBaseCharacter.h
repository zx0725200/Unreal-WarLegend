// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "WarLegendBaseCharacter.generated.h"

class UCharDataConfig;
class UCharAttributeSet;
class UCharAbilitySystemComponent;

UCLASS()
class WARLEGEND_API AWarLegendBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWarLegendBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UCharAbilitySystemComponent* GetWarriorAbilitySystemComponent() const { return CharAbilitySystemComponent; }
	UCharAttributeSet* GetWarriorAttributeSet() const { return CharAttributeSet; }
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UCharAbilitySystemComponent> CharAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UCharAttributeSet> CharAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharData")
	TSoftObjectPtr<UCharDataConfig> CharDataConfig;
};
