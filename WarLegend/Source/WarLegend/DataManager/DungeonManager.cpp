// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonManager.h"

#include "TableManager.h"
#include "DataTable/DungeonTableData.h"

void UDungeonManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDungeonManager::EnterDungeon(const int32 InDungeonID)
{
	UTableManager* TableMgr = GetGameInstance()->GetSubsystem<UTableManager>();
	if (!TableMgr) return;

	const auto* DungeonTableData = TableMgr->GetDungeonTableData(InDungeonID);
	if (!DungeonTableData) return;

	TeleportPlayer(DungeonTableData->SpawnLocation);

	UE_LOG(LogTemp, Log, TEXT("[DungeonManager] 던전 입장 - ID: %d | %s"), InDungeonID, *DungeonTableData->DungeonName);
}

void UDungeonManager::ExitDungeon()
{
	const FVector TownLocation = FVector(1780.f, -1153.f, 302.f);
	TeleportPlayer(TownLocation);
}

void UDungeonManager::TeleportPlayer(const FVector& InLocation) const
{
	// Todo : 이펙트 추가하면 이펙트가 끝나는 시점에 호출.
	
	const UWorld* World = GetGameInstance()->GetWorld();
	if (!World) return;

	APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) return;

	PlayerPawn->SetActorLocation(InLocation);
}
