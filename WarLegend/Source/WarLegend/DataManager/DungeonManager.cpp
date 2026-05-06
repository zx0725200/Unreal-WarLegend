// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonManager.h"

#include "TableManager.h"
#include "Controller/WarLegendPlayerController.h"
#include "DataTable/DungeonTableData.h"
#include "ETC/Constant.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"

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
	
	ChangePlayerState(EPlayerLocType::Battle);
	TeleportPlayer(Constant::PlayerSpawnLocation);
}

void UDungeonManager::ExitDungeon()
{
	ChangePlayerState(EPlayerLocType::City);
	TeleportPlayer(Constant::PlayerSpawnLocation);
	
}

void UDungeonManager::TeleportPlayer(const FVector& InLocation) const
{
	// Todo : 이펙트 추가하면 이펙트가 끝나는 시점에 호출.
	
	const UWorld* World = GetGameInstance()->GetWorld();
	VALID_RETURN(World);

	auto* PlayerController = Cast<AWarLegendPlayerController>(World->GetFirstPlayerController());
	VALID_RETURN(PlayerController);

	PlayerController->ChangeLocation(InLocation);
}

void UDungeonManager::ChangePlayerState(const EPlayerLocType InType)
{
	const UWorld* World = GetGameInstance()->GetWorld();
	VALID_RETURN(World);

	auto* PlayerController = Cast<AWarLegendPlayerController>(World->GetFirstPlayerController());
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
