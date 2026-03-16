// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TableManager.generated.h"

enum class EItemType : uint8;
struct FItemTableData;

namespace DataTableCacheUtil
{
	template<typename RowT, typename KeyT, typename KeyFunc>
	void BuildByKey(UDataTable* Table, TMap<KeyT, TArray<RowT*>>& OutCache, KeyFunc GetKey)
	{
		OutCache.Empty();
		if (!Table) return;

		static const FString Context(TEXT("BuildByKey"));
		TArray<RowT*> Rows;
		Table->GetAllRows(Context, Rows);

		for (RowT* Row : Rows)
		{
			if (!Row) continue;
			OutCache.FindOrAdd(GetKey(*Row)).Add(Row);
		}
	}
}

struct FDungeonTableData;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UTableManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UTableManager();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FItemTableData* GetItemTableData(const int32 InItemId);
	
	TArray<FDungeonTableData*> GetDungeonTableData();		// 전체 던전 데이터
	TArray<FItemTableData*> GetAllItemTableData() const;	// 전체 아이템 데이터
	TArray<EItemType> GetLeftEquipTypes() const;			// Weapon ~ Glove
	TArray<EItemType> GetRightEquipTypes() const;			// BossWeapon ~ BossArmor
	FString GetItemTypeName(const EItemType InItemType);	

private:
	void LoadTable(UDataTable* Table);
	
private:
	TSoftObjectPtr<UDataTable> DungeonTableAsset;
	TSoftObjectPtr<UDataTable> ItemTableAsset;
	
	TMap<int32, TArray<FDungeonTableData*>> DungeonTableData;
	TMap<int32, TArray<FItemTableData*>> ItemTableData;
};
