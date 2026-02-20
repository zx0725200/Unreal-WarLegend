// Fill out your copyright notice in the Description page of Project Settings.


#include "TableManager.h"

#include "DataTable/DungeonTableData.h"

UTableManager::UTableManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Finder(TEXT("/Script/Engine.DataTable'/Game/Table/DataDungeon.DataDungeon'"));
	if (Finder.Succeeded())
	{
		DungeonTableAsset = Finder.Object;
	}
}

void UTableManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (!DungeonTableAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("[DungeonTierCache] DataTable is null"));
		return;
	}

	LoadTable(DungeonTableAsset.Get());
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
	DataTableCacheUtil::BuildByKey<FDungeonTableData, int32>(
		Table,
		DungeonTableData,
		[](const FDungeonTableData& R) { return R.DungeonID; }
	);
}
