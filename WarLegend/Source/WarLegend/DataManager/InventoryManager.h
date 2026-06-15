// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETC/Struct.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "InventoryManager.generated.h"

enum class EItemType : uint8;
/**
 *
 */
UCLASS()
class WARLEGEND_API UInventoryManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FMyItem GetSelectedItemData();
	const TArray<FMyItem>& GetInventoryItemData() const { return InventoryItemData; }

	// 뽑기 결과 아이템 ID를 인벤토리에 추가
	void AddItem(const int32 InItemID);
	void AddItems(const TArray<int32>& InItemList);
	void ResetItem();
	void SetSelectedItem(const int32 InUniqueID);

	// 장착
	void EquipItem(const int32 InUniqueID);
	void UnequipItem(const EItemType InItemType);
	const FMyItem* FindEquippedItemData(const EItemType InItemType) const;
	bool IsEquippedItem(const int32 InUniqueID) const;
	FEquipStatTotal GetEquippedStatTotal() const;

	// 같은 타입 장착템보다 능력치 합이 높은 업그레이드인지 검사
	bool IsUpgrade(const FMyItem& InItem) const;

	// 세이브에 설정된 등급 필터에 해당하는 (장착하지 않은) 아이템을 모두 버린다.
	void DiscardItemsByFilter();

private:
	void Internal_AddItem(const int32 InItemID);
	void SaveData() const;
	void LoadData();

private:
	UPROPERTY()
	TArray<FMyItem> InventoryItemData;

	// 아이템 타입 -> 장착 중인 아이템의 인벤토리 UniqueID
	UPROPERTY()
	TMap<EItemType, int32> EquippedItems;

	int32 SelectedItemID = INDEX_NONE;
	int32 UniqueInventoryItemID = 0;
};
