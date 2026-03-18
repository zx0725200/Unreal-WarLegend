// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DungeonManager.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UDungeonManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override; 
	
	void EnterDungeon(const int32 InDungeonID);
	void ExitDungeon();
	
private:
	void TeleportPlayer(const FVector& InLocation) const;
};
