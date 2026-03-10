// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"

#include "ViewModel/Slot/SlotInventoryVM.h"

void UInventoryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	for (int32 i=0; i<10; i++)
	{
		USlotInventoryVM* SlotInventoryVM = NewObject<USlotInventoryVM>(this);
		SlotInventoryVM->ID = i;
	
		InventoryItemData.Emplace(SlotInventoryVM);
	}
}

void UInventoryManager::AddItem(const int32 InItemID)
{
	if (InItemID == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("[InventoryManager] 유효하지 않은 아이템 ID입니다."));
		return;
	}

	USlotInventoryVM* ItemData = NewObject<USlotInventoryVM>(this);
	ItemData->ID = InItemID;
	InventoryItemData.Emplace(ItemData);

	UE_LOG(LogTemp, Log, TEXT("[InventoryManager] 아이템 추가됨 ID: %d | 총 보유: %d"), InItemID, InventoryItemData.Num());
}

void UInventoryManager::AddItems(const TArray<int32>& InItemList)
{
	for (const int32 ItemID : InItemList)
	{
		AddItem(ItemID);
	}
}
