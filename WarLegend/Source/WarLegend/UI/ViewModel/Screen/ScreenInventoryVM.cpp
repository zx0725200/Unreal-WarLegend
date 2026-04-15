// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenInventoryVM.h"
#include "DataManager/InventoryManager.h"
#include "DataManager/TableManager.h"
#include "ETC/Define.h"
#include "ViewModel/Slot/SlotInventoryVM.h"

void UScreenInventoryVM::Init()
{
	Super::Init();
	
	UTableManager* TableMgr = GetTableManager();
	VALID_RETURN(TableMgr);
	
	for (const EItemType ItemType : GetTableManager()->GetLeftEquipTypes())
	{
		LeftItemTypes.Emplace(ItemType, TableMgr->GetItemTypeName(ItemType));
	}
		
	for (const EItemType ItemType : TableMgr->GetRightEquipTypes())
	{
		RightItemTypes.Emplace(ItemType, TableMgr->GetItemTypeName(ItemType));
	}
	
	RefreshItems();
}

void UScreenInventoryVM::RefreshItems()
{
	Items.Empty();
    
	const auto InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);
	
	for (const FMyItem& MyItem : InvenMgr->GetInventoryItemData())
	{
		USlotInventoryVM* SlotVM = NewObject<USlotInventoryVM>(this);
		SlotVM->Init(MyItem);
		Items.Emplace(SlotVM);
	}
}

void UScreenInventoryVM::OnReset()
{
	const auto InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);
	
	InvenMgr->ResetItem();
}
