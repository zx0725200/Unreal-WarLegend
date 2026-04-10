// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CommonAbilityBase.generated.h"

enum class ECharAbilityApplyType : uint8;
class UHeroAbilitySystemComponent;
class UHeroCombatComponent;

UCLASS()
class WARLEGEND_API UCommonAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// 블루프린트 호출 용
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	UHeroAbilitySystemComponent* GetHeroAbilityComponentFromActorInfo() const;
};
