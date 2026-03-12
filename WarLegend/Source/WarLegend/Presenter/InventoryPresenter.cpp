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
		
		for (uint8 Value = static_cast<uint8>(EItemType::Weapon); Value <= static_cast<uint8>(EItemType::Glove); ++Value)
		{
			const EItemType InItemType = static_cast<EItemType>(Value);
			const FString ItemTypeName = TableMgr->GetItemTypeName(InItemType);
			
			InventoryData->LeftItemTypes.Emplace(InItemType, ItemTypeName);
		}
		
		for (uint8 Value = static_cast<uint8>(EItemType::BossWeapon); Value <= static_cast<uint8>(EItemType::BossArmor); ++Value)
		{
			const EItemType InItemType = static_cast<EItemType>(Value);
			const FString ItemTypeName = TableMgr->GetItemTypeName(InItemType);
			
			InventoryData->RightItemTypes.Emplace(InItemType, ItemTypeName);
		}
		
		ScreenInventory->SetViewModel(InventoryData);
		ScreenInventory->Init();
	}
}
