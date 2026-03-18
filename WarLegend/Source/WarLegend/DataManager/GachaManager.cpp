// Fill out your copyright notice in the Description page of Project Settings.


#include "GachaManager.h"

#include "SaveGameDataManager.h"
#include "TableManager.h"
#include "DataAsset/WLSaveGame.h"
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

void UGachaManager::ApplyFilter()
{
	auto* SaveGameMgr = GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	UWLSaveGame* Save = SaveGameMgr->GetSaveGame();
	if (!Save) return;

	TArray<EItemGrade> AllowedGrades;
	for (const auto& [Grade, bChecked] : Save->GachaFilter)
	{
		if (!bChecked) continue;
		AllowedGrades.Emplace(Grade);
	}
	SetFilter(AllowedGrades);
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
		{ EItemGrade::Normal, 55.f },
		{ EItemGrade::Rare,   30.f },
		{ EItemGrade::Unique, 11.f },
		{ EItemGrade::Legend,  3.f },
		{ EItemGrade::Epic,    1.f },
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
	const float TotalWeight = GetTotalWeight();
	const float ItemWeight = FMath::FRandRange(0.f, TotalWeight);
	float ItemAccumulation = 0.f;
	
	EItemGrade ResultGrade = EItemGrade::None;
	for (const FGachaGradeWeight& Item : GradeWeightTable)
	{
		ItemAccumulation += Item.Weight;
		if (ItemWeight <= ItemAccumulation)
		{
			ResultGrade = Item.Grade;
			break;
		}
	}
	
	// 필터에 포함된건 꽝 처리
	if (FilterGrades.Contains(ResultGrade))
	{
		return EItemGrade::None;
	}
	
	return ResultGrade;
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

float UGachaManager::GetTotalWeight() const
{
	float TotalWeight = 0.f;
	for (const FGachaGradeWeight& Item : GradeWeightTable)
	{
		TotalWeight += Item.Weight;
	}
	
	return TotalWeight;
}
	
