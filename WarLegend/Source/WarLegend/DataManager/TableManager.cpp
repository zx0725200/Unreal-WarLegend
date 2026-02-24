// Fill out your copyright notice in the Description page of Project Settings.


#include "TableManager.h"

#include "DataTable/DungeonTableData.h"
#include "DataTable/ItemTableData.h"

UTableManager::UTableManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DungeonTableFinder(TEXT("/Script/Engine.DataTable'/Game/Table/DataDungeon_Dummy.DataDungeon_Dummy'"));
	if (DungeonTableFinder.Succeeded())
	{
		DungeonTableAsset = DungeonTableFinder.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemTableFinder(TEXT("/Script/Engine.DataTable'/Game/Table/DataItem.DataItem'"));
	if (ItemTableFinder.Succeeded())
	{
		ItemTableAsset = ItemTableFinder.Object;
	}
}

void UTableManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (!DungeonTableAsset || !ItemTableAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("DataTable is null"));
		return;
	}

	LoadTable(DungeonTableAsset.Get());
	LoadTable(ItemTableAsset.Get());
}

TArray<const FDungeonTableData*> UTableManager::GetDungeonTableData()
{
	TArray<const FDungeonTableData*> OutTableData;
	
	int32 TotalNum = 0;
	for (const auto& Pair : DungeonTableData)
	{
		TotalNum += Pair.Value.Num();
	}
	OutTableData.Reserve(TotalNum);
	
	for (const auto& Pair : DungeonTableData)
	{
		for (const FDungeonTableData* Ptr : Pair.Value)
		{
			if (!Ptr) continue;
			OutTableData.Add(Ptr);
		}
	}
	
	return OutTableData;
}

void UTableManager::LoadTable(UDataTable* Table)
{
	if (Table == DungeonTableAsset)
	{
		DataTableCacheUtil::BuildByKey<FDungeonTableData, int32>(
			Table,
			DungeonTableData,
			[](const FDungeonTableData& R) { return R.DungeonID; }
		);
	}
	else if (Table == ItemTableAsset)
	{
		DataTableCacheUtil::BuildByKey<FItemTableData, int32>(
			Table,
			ItemTableData,
			[](const FItemTableData& R) { return R.ID; }
		);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTableManager::LoadTable] Unknown table: %s"), *GetNameSafe(Table));
	}
}
