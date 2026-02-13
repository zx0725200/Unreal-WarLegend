// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WarLegendGameMode.generated.h"

UCLASS(abstract)
class AWarLegendGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWarLegendGameMode();
	
	virtual void BeginPlay() override;
	
};



