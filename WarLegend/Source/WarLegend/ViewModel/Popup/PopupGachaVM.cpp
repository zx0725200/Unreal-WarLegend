// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaVM.h"

#include "PopupGachaLogVM.h"
#include "DataManager/GachaManager.h"
#include "DataManager/InventoryManager.h"
#include "DataManager/TableManager.h"
#include "DataManager/UIManagerImpl.h"
#include "DataTable/ItemTableData.h"
#include "ETC/Struct.h"

void UPopupGachaVM::Init(UGachaManager* InGachaMgr, UInventoryManager* InInvenMgr, UTableManager* InTableMgr, UUIManagerImpl* InUIMgr, UPopupGachaLogVM* InLogVM)
{
	GachaMgr = InGachaMgr;
	InvenMgr = InInvenMgr;
	TableMgr = InTableMgr;
	UIMgr    = InUIMgr;
	LogVM    = InLogVM;
}

void UPopupGachaVM::BroadCastOne()
{
	if (!GachaMgr || !InvenMgr) return;
	
	const int32 ItemID = GachaMgr->GetGachaItem();
	if (ItemID == -1) return;
	
	InvenMgr->AddItem(ItemID);
	ShowToast(ItemID);
}

void UPopupGachaVM::BroadCastTen()
{
	if (!GachaMgr || !InvenMgr) return;
	
	const TArray<int32> ItemIDs = GachaMgr->GetGachaItemMultiple(10);
	
	InvenMgr->AddItems(ItemIDs);
	ShowToastMulti(ItemIDs);
}

void UPopupGachaVM::BroadCastAll()
{
	if (!GachaMgr || !InvenMgr) return;
	
	const TArray<int32> ItemIDs = GachaMgr->GetGachaItemMultiple(30);
	
	InvenMgr->AddItems(ItemIDs);
	ShowToastMulti(ItemIDs);
}

void UPopupGachaVM::ShowToast(int32 InItemID)
{
	if (!TableMgr || !UIMgr || !LogVM) return;
	const auto* TableData = TableMgr->GetItemTableData(InItemID);
	if (!TableData) return;

	FGachaLogData Data;
	Data.ItemName   = TableData->ItemName;
	Data.GradeColor = UIMgr->GetItemColor(TableData->ItemGrade);
	Data.Time       = FDateTime::Now().ToString(TEXT("%H:%M:%S"));
	LogVM->AddLog(Data);
	
	OnToastRequested.Broadcast();
}

void UPopupGachaVM::ShowToastMulti(const TArray<int32>& InItemIDs)
{
	for (const int32 ID : InItemIDs)
	{
		ShowToast(ID);
	}
}
