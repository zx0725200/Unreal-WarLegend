// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPresenter.h"

#include "DataManager/TableManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Popup/PopupItemInfo.h"
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
		InventoryData->Init(InvenMgr, TableMgr);
		InventoryData->GetOnItemInfoRequested().AddUObject(this, &UInventoryPresenter::HandleOpenItemInfo);
		
		ScreenInventory->SetViewModel(InventoryData);
	}
}

void UInventoryPresenter::HandleOpenItemInfo(const FMyItem& InItem)
{
	auto* Popup = UIMgr->ShowUI<UPopupItemInfo>(TEXT("PopupItemInfo"));
	if (!Popup) return;
}
