// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPresenter.h"

#include "DataManager/TableManager.h"
#include "DataManager/UIManagerImpl.h"
#include "ETC/Enum.h"
#include "Screen/ScreenInventory.h"
#include "ViewModel/Screen/ScreenInventoryVM.h"

void UInventoryPresenter::Init(UUIManagerImpl* InUIMgr, UInventoryManager* InInvenMgr, UTableManager* InTableMgr)
{
	UIMgr = InUIMgr;
	InvenMgr = InInvenMgr;
	TableMgr = InTableMgr;
}

void UInventoryPresenter::OpenScreenInventory()
{
	if (!InvenMgr || !UIMgr || !TableMgr) return;
	
	if (auto* ScreenInventory = UIMgr->ShowUI<UScreenInventory>(TEXT("ScreenInventory")))
	{
		UScreenInventoryVM* InventoryData = NewObject<UScreenInventoryVM>(ScreenInventory);
		InventoryData->Init(InvenMgr);
		
		for (const EItemType ItemType : TableMgr->GetLeftEquipTypes())
		{
			InventoryData->LeftItemTypes.Emplace(ItemType, TableMgr->GetItemTypeName(ItemType));
		}
		
		for (const EItemType ItemType : TableMgr->GetRightEquipTypes())
		{
			InventoryData->RightItemTypes.Emplace(ItemType, TableMgr->GetItemTypeName(ItemType));
		}
		
		ScreenInventory->SetViewModel(InventoryData);
		ScreenInventory->Init();
	}
}
