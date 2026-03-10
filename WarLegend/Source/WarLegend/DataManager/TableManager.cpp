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

TArray<FDungeonTableData*> UTableManager::GetDungeonTableData()
{
	TArray<FDungeonTableData*> OutTableData;
	
	int32 TotalNum = 0;
	for (const auto& Pair : DungeonTableData)
	{
		TotalNum += Pair.Value.Num();
	}
	OutTableData.Reserve(TotalNum);
	
	for (const auto& Pair : DungeonTableData)
	{
		for (FDungeonTableData* Ptr : Pair.Value)
		{
			if (!Ptr) continue;
			OutTableData.Add(Ptr);
		}
	}
	
	return OutTableData;
}

TArray<FItemTableData*> UTableManager::GetAllItemTableData() const
{
	TArray<FItemTableData*> OutItems;

	int32 TotalNum = 0;
	for (const auto& Pair : ItemTableData)
	{
		TotalNum += Pair.Value.Num();
	}
	OutItems.Reserve(TotalNum);

	for (const auto& Pair : ItemTableData)
	{
		for (FItemTableData* Ptr : Pair.Value)
		{
			if (!Ptr) continue;
			OutItems.Add(Ptr);
		}
	}

	return OutItems;
}

FString UTableManager::GetItemTypeName(const EItemType ItemType)
{
	for (const auto& Pair : ItemTableData)
	{
		for (const FItemTableData* Ptr : Pair.Value)
		{
			if (!Ptr) continue;
			if (Ptr->ItemType == ItemType)
			{
				return Ptr->ItemTypeName;
			}
		}
	}
	
	return TEXT("");
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
