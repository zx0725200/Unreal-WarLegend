// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaVM.h"

#include "PopupGachaLogVM.h"
#include "GachaManager.h"
#include "InventoryManager.h"
#include "TableManager.h"
#include "UIManagerImpl.h"
#include "DataTable/ItemTableData.h"
#include "ETC/Define.h"
#include "ETC/Struct.h"

void UPopupGachaVM::Init()
{
	Super::Init();
}

void UPopupGachaVM::OnGachaOne()
{
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);
	
	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(GachaMgr);
	
	const int32 ItemID = GachaMgr->GetGachaItem();
	if (ItemID == -1) return;
	
	InvenMgr->AddItem(ItemID);
	ShowToast(ItemID);
}

void UPopupGachaVM::OnGachaMulti(const int32 InItemCount)
{
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);
	
	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(GachaMgr);
	
	const TArray<int32> ItemIDs = GachaMgr->GetGachaItemMultiple(InItemCount);
	
	InvenMgr->AddItems(ItemIDs);
	ShowToastMulti(ItemIDs);
}

void UPopupGachaVM::ShowToast(int32 InItemID)
{
	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);
	
	UTableManager* TableMgr = GetTableManager();
	VALID_RETURN(TableMgr);
	
	if (!LogVM) return;
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
