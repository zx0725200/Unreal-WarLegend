// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DungeonManager.generated.h"

enum class EPlayerLocType : uint8;
class AMonster;
class AWLPatrolPathActor;
 
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMonsterSpawned, AMonster*, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMonsterLapChanged, AMonster*, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMonsterRemoved, AMonster*);
DECLARE_MULTICAST_DELEGATE(FOnDungeonFailed);

UCLASS()
class WARLEGEND_API UDungeonManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override; 
	
	void EnterDungeon(const int32 InDungeonID);
	void ExitDungeon();

private:
	void ChangePlayerState(const EPlayerLocType InType);
	
	void TeleportPlayer(const FVector& InLocation) const;
};
