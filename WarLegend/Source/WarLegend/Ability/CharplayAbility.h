// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CharplayAbility.generated.h"

UENUM(BlueprintType)
enum class ECharAbilityActivation : uint8
{
	OnTriggered,
	OnGiven
};


/**
 * 
 */
UCLASS()
class WARLEGEND_API UCharplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "CharAbility")
	ECharAbilityActivation AbilityActivation = ECharAbilityActivation::OnTriggered;
};
