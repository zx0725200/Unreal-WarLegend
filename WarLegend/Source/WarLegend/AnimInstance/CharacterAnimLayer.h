// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimInstanceBase.h"
#include "CharacterAnimLayer.generated.h"

class UCharacterAnimInstance;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UCharacterAnimLayer : public UCharacterAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UCharacterAnimInstance* GetCharacterAnimInstance();
};
