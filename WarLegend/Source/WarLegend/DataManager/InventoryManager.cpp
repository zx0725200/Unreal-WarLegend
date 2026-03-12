// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"

#include "TableManager.h"
#include "UIManager.h"
#include "UIManagerImpl.h"
#include "DataTable/ItemTableData.h"
#include "ETC/Define.h"
#include "ViewModel/Slot/SlotInventoryVM.h"

void UInventoryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UInventoryManager::AddItem(const int32 InItemID)
{
	if (InItemID == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("[InventoryManager] 유효하지 않은 아이템 ID입니다."));
		return;
	}

	UTableManager* TableMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<UTableManager>();
	if (!TableMgr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GachaManager] TableManager를 찾을 수 없습니다."));
		return;
	}
	
	const auto ItemTableData = TableMgr->GetItemTableData(InItemID);
	if (!ItemTableData) return;
	
	USlotInventoryVM* ItemData = NewObject<USlotInventoryVM>(this);
	ItemData->ID = InItemID;
	ItemData->ItemName = ItemTableData->ItemName;
	ItemData->ItemTypeName = ItemTableData->ItemTypeName;
	ItemData->ItemGradeColor = GTGetMgrImpl(UIManager)->GetItemColor(ItemTableData->ItemGrade);
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
