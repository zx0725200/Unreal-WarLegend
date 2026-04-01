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
	
	void InitDungeonSetting();
	void EnterDungeon(const int32 InDungeonID);
	void ExitDungeon();
	
	int32 GetAliveCount() const { return MonsterList.Num(); }
 
	FOnMonsterSpawned& GetOnMonsterSpawned() { return OnMonsterSpawned; }
	FOnMonsterLapChanged& GetOnMonsterLapChanged() { return OnMonsterLapChanged; }
	FOnMonsterRemoved& GetOnMonsterRemoved() { return OnMonsterRemoved; }
	FOnDungeonFailed& GetOnDungeonFailed() { return OnDungeonFailed; }
	
private:
	void SpawnMonster();
	void HandleLapCountChanged(AMonster* InMonster, const int32 InNewLapCount);
	void HandleMonsterDead(AMonster* InMonster);
	void HandleMonsterWin();
	
	void ChangePlayerState(const EPlayerLocType InType);
	
	void TeleportPlayer(const FVector& InLocation) const;
	
	AWLPatrolPathActor* GetPatrolPath();
	
private:
	UPROPERTY()
	TObjectPtr<AWLPatrolPathActor> CachedPatrolPathActor;
	
	UPROPERTY()
	TSubclassOf<AMonster> MonsterClass;
 
	UPROPERTY()
	TArray<TObjectPtr<AMonster>> MonsterList;
 
	FOnMonsterSpawned OnMonsterSpawned;
	FOnMonsterLapChanged OnMonsterLapChanged;
	FOnMonsterRemoved OnMonsterRemoved;
	FOnDungeonFailed OnDungeonFailed;
	
	int32 SpawnedCount = 0;
	
	FTimerHandle SpawnTimerHandle;
	FTimerHandle ExitTimerHandle;
};
