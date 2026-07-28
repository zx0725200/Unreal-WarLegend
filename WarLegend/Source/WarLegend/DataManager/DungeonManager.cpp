// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonManager.h"

#include "TableManager.h"
#include "Camera/PlayerCameraManager.h"
#include "Character/WarLegendCharacter.h"
#include "Controller/WarLegendPlayerController.h"
#include "DataTable/DungeonTableData.h"
#include "Engine/World.h"
#include "ETC/Constant.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "TimerManager.h"

void UDungeonManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDungeonManager::EnterDungeon(const int32 InDungeonID)
{
	UTableManager* TableMgr = GetGameInstance()->GetSubsystem<UTableManager>();
	VALID_RETURN(TableMgr);

	const auto* DungeonTableData = TableMgr->GetDungeonTableData(InDungeonID);
	VALID_RETURN(DungeonTableData);

	// 보스 아레나 좌표(테이블). 미설정(Zero)이면 기본 스폰 위치로 폴백.
	PendingArenaLocation = DungeonTableData->SpawnLocation.IsNearlyZero()
		? Constant::PlayerSpawnLocation
		: DungeonTableData->SpawnLocation;

	AWarLegendPlayerController* PC = GetPlayerController();
	VALID_RETURN(PC);

	// ① 화면을 검정으로 페이드 아웃(끝난 뒤 검정 유지).
	if (PC->PlayerCameraManager)
	{
		PC->PlayerCameraManager->StartCameraFade(0.f, 1.f, Constant::DungeonFadeOutTime, FLinearColor::Black, false, true);
	}

	// 검정 화면 뒤에서 셋업하도록 페이드 아웃 시간 후 콜백.
	const UWorld* World = GetGameInstance()->GetWorld();
	VALID_RETURN(World);
	World->GetTimerManager().SetTimer(EntryFadeTimer, this, &UDungeonManager::HandleEntryFadeOutComplete, Constant::DungeonFadeOutTime, false);
}

void UDungeonManager::HandleEntryFadeOutComplete()
{
	AWarLegendPlayerController* PC = GetPlayerController();
	VALID_RETURN(PC);

	// ② 배틀 모드(인풋 매핑 + 카메라) 전환.
	ChangePlayerState(EPlayerLocType::Battle);

	// ③ 아레나 상공으로 텔레포트 → 낙하 시작.
	const FVector DropLocation = PendingArenaLocation + FVector(0.f, 0.f, Constant::DungeonEntryDropHeight);
	TeleportPlayer(DropLocation);

	if (AWarLegendCharacter* Hero = Cast<AWarLegendCharacter>(PC->GetPawn()))
	{
		Hero->BeginDungeonEntry();
	}

	// 낙하 연출 동안 입력 잠금(착지 시 복구).
	PC->DisableInput(PC);

	// ④ 밝아지며 낙하하도록 페이드 인.
	if (PC->PlayerCameraManager)
	{
		PC->PlayerCameraManager->StartCameraFade(1.f, 0.f, Constant::DungeonFadeInTime, FLinearColor::Black, false, false);
	}
}

void UDungeonManager::OnPlayerEntryLanded()
{
	// ⑤ 착지 → 입력 복구 + 보스전 시작 브로드캐스트.
	if (AWarLegendPlayerController* PC = GetPlayerController())
	{
		PC->EnableInput(PC);
	}

	OnBattleStarted.Broadcast();
}

AWarLegendPlayerController* UDungeonManager::GetPlayerController() const
{
	const UWorld* World = GetGameInstance()->GetWorld();
	if (!World) return nullptr;

	return Cast<AWarLegendPlayerController>(World->GetFirstPlayerController());
}

void UDungeonManager::ExitDungeon()
{
	ChangePlayerState(EPlayerLocType::City);
	TeleportPlayer(Constant::PlayerSpawnLocation);
	
}

void UDungeonManager::TeleportPlayer(const FVector& InLocation) const
{
	AWarLegendPlayerController* PlayerController = GetPlayerController();
	VALID_RETURN(PlayerController);

	PlayerController->ChangeLocation(InLocation);
}

void UDungeonManager::ChangePlayerState(const EPlayerLocType InType)
{
	AWarLegendPlayerController* PlayerController = GetPlayerController();
	VALID_RETURN(PlayerController);

	if (InType == EPlayerLocType::Battle)
	{
		PlayerController->ChangeBattle();
	}
	else if (InType == EPlayerLocType::City)
	{
		PlayerController->ChangeCity();
	}
}
