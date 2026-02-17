// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "CharacterDataManager.generated.h"

/**
 * 
 */

UCLASS()
class WARLEGEND_API UCharacterDataManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual auto Initialize(FSubsystemCollectionBase& Collection) -> void override;
	virtual void Deinitialize() override;
};
