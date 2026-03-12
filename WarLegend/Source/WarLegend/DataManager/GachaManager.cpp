// Fill out your copyright notice in the Description page of Project Settings.


#include "GachaManager.h"

#include "TableManager.h"
#include "DataTable/ItemTableData.h"

void UGachaManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	Collection.InitializeDependency<UTableManager>(); // TableManager 먼저 보장
	
	BuildCache();
}

int32 UGachaManager::GetGachaItem() const
{
	const EItemGrade SelectedGrade = GetSelectedGrade();
	return GetSelectedItemByGrade(SelectedGrade);
}

TArray<int32> UGachaManager::GetGachaItemMultiple(const int32 InCount) const
{
	TArray<int32> GachaItemIdList;
	GachaItemIdList.Reserve(InCount);

	for (int32 i = 0; i < InCount; i++)
	{
		int32 ItemID = GetGachaItem();
		if (ItemID != -1)
		{
			GachaItemIdList.Emplace(ItemID);
		}
	}

	return GachaItemIdList;
}

void UGachaManager::SetFilter(const TArray<EItemGrade>& InAllowedGrades)
{
	FilterGrades = InAllowedGrades;
	FilterGrades.AddUnique(EItemGrade::Epic); // 최고등급 항상 포함
}

void UGachaManager::BuildCache()
{
	// 등급별 가중치 설정
	GradeWeightTable = {
		{ EItemGrade::Normal, 50.f },
		{ EItemGrade::Rare,   30.f },
		{ EItemGrade::Unique, 12.f },
		{ EItemGrade::Legend,  5.f },
		{ EItemGrade::Epic,    3.f },
	};
	
	UTableManager* TableMgr = GetGameInstance()->GetSubsystem<UTableManager>();
	if (!TableMgr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GachaManager] TableManager를 찾을 수 없습니다."));
		return;
	}

	TArray<FItemTableData*> AllItems = TableMgr->GetAllItemTableData();
	for (const FItemTableData* Item : AllItems)
	{
		if (!Item || Item->ItemGrade == EItemGrade::None) continue;
		GradeToItemIDs.FindOrAdd(Item->ItemGrade).Add(Item->ID);
	}
}

EItemGrade UGachaManager::GetSelectedGrade() const
{
	float TotalFilter = 0.f;
	for (const FGachaGradeWeight& Item : GradeWeightTable)
	{
		if (FilterGrades.Contains(Item.Grade))
		{
			TotalFilter += Item.Weight;
		}
	}

	const float ItemWeight = FMath::FRandRange(0.f, TotalFilter);
	float ItemAccumulation = 0.f;

	for (const FGachaGradeWeight& Item : GradeWeightTable)
	{
		if (!FilterGrades.Contains(Item.Grade)) continue;

		ItemAccumulation += Item.Weight;
		if (ItemWeight <= ItemAccumulation)
		{
			return Item.Grade;
		}
	}

	return GradeWeightTable.Last().Grade;
}

int32 UGachaManager::GetSelectedItemByGrade(const EItemGrade InGrade) const
{
	const TArray<int32>* Items = GradeToItemIDs.Find(InGrade);
	if (!Items || Items->IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("[GachaManager] 등급 %d에 해당하는 아이템이 없습니다."), (int32)InGrade);
		return -1;
	}

	const int32 RandomIndex = FMath::RandRange(0, Items->Num() - 1);
	return (*Items)[RandomIndex];
}
	
