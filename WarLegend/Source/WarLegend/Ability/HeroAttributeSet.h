// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "HeroAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class WARLEGEND_API UHeroAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	// GamePlayEffect 테이블 속성용.
	UHeroAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category = "HP")
	FGameplayAttributeData CurrentHp;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, CurrentHp)
	
	UPROPERTY(BlueprintReadOnly, Category = "HP")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, MaxHp)
	
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, AttackPower)
	
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, DefensePower)
};
