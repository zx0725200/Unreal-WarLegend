// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TimerHandle.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DungeonManager.generated.h"

enum class EPlayerLocType : uint8;
class AMonster;
class AWLPatrolPathActor;
class AWarLegendPlayerController;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMonsterSpawned, AMonster*, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMonsterLapChanged, AMonster*, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMonsterRemoved, AMonster*);
DECLARE_MULTICAST_DELEGATE(FOnDungeonFailed);
DECLARE_MULTICAST_DELEGATE(FOnDungeonBattleStarted); // 입장 연출 끝(착지)나고 보스전 시작 시점

UCLASS()
class WARLEGEND_API UDungeonManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override; 
	
	void EnterDungeon(const int32 InDungeonID);
	void ExitDungeon();

	// 낙하 착지 시 플레이어 캐릭터가 호출(입력 복구 + 보스전 시작 알림).
	void OnPlayerEntryLanded();

	FOnDungeonBattleStarted& GetOnBattleStarted() { return OnBattleStarted; }

private:
	void ChangePlayerState(const EPlayerLocType InType);

	void TeleportPlayer(const FVector& InLocation) const;

	// 페이드 아웃(검정)이 끝난 뒤 검정 화면 뒤에서 배틀 전환 + 상공 텔레포트 + 페이드 인.
	void HandleEntryFadeOutComplete();

	AWarLegendPlayerController* GetPlayerController() const;

private:
	// 입장 연출에서 낙하할 목표 아레나 좌표(테이블 SpawnLocation).
	FVector PendingArenaLocation = FVector::ZeroVector;

	FTimerHandle EntryFadeTimer;

	FOnDungeonBattleStarted OnBattleStarted;
};
