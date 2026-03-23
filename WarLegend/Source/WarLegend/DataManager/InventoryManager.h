// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "InventoryManager.generated.h"

struct FMyItem;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UInventoryManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	const TArray<FMyItem>& GetInventoryItemData() const { return InventoryItemData; }
	
	// 뽑기 결과 아이템 ID를 인벤토리에 추가
	void AddItem(const int32 InItemID);
	void AddItems(const TArray<int32>& InItemList);
	void ResetItem();
	
private:
	void Internal_AddItem(const int32 InItemID);
	void SaveData() const;
	void LoadData();
	
private:
	UPROPERTY()
	TArray<FMyItem> InventoryItemData;
	
	int32 UniqueInventoryItemID;
};
