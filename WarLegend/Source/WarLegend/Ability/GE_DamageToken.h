// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GE_DamageToken.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UGE_DamageToken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UGE_DamageToken();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
