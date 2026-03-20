// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenInventoryVM.h"

#include "DataManager/TableManager.h"
#include "ViewModel/Slot/SlotInventoryVM.h"

void UScreenInventoryVM::Init(UInventoryManager* InMgr, UTableManager* TableMgr)
{
	InvenMgr = InMgr;
	
	for (const EItemType ItemType : TableMgr->GetLeftEquipTypes())
	{
		LeftItemTypes.Emplace(ItemType, TableMgr->GetItemTypeName(ItemType));
	}
		
	for (const EItemType ItemType : TableMgr->GetRightEquipTypes())
	{
		RightItemTypes.Emplace(ItemType, TableMgr->GetItemTypeName(ItemType));
	}
}

void UScreenInventoryVM::RefreshItems()
{
	Items.Empty();
    
	for (const FMyItem& MyItem : InvenMgr->GetInventoryItemData())
	{
		USlotInventoryVM* SlotVM = NewObject<USlotInventoryVM>(this);
		SlotVM->FromSaveData(MyItem);
		Items.Emplace(SlotVM);
	}
}

const TArray<TObjectPtr<USlotInventoryVM>>& UScreenInventoryVM::GetItems() const
{
	return Items;
}

const TMap<EItemType, FString>& UScreenInventoryVM::GetLeftItemTypes() const
{
	return LeftItemTypes;
}

const TMap<EItemType, FString>& UScreenInventoryVM::GetLightItemTypes() const
{
	return RightItemTypes;
}
