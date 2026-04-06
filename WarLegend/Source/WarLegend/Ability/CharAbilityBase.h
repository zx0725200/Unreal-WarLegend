// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CharAbilityBase.generated.h"

class UCharAbilitySystemComponent;
class UCharCombatComponent;

UENUM(BlueprintType)
enum class ECharAbilityActivation : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class WARLEGEND_API UCharAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UCharCombatComponent* GetPawnCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UCharAbilitySystemComponent* GetCharAbilityComponentFromActorInfo() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "CharAbility")
	ECharAbilityActivation AbilityActivation = ECharAbilityActivation::OnTriggered;
};
