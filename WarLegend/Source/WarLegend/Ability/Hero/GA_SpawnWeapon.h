// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Base/CommonAbilityBase.h"
#include "GA_SpawnWeapon.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UGA_SpawnWeapon : public UCommonAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
