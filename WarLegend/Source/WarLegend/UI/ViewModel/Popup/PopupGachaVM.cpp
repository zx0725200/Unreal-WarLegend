// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaVM.h"

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
	VALID_RETURN(InvenMgr);

	const int32 ItemID = GachaMgr->GetGachaItem();
	if (ItemID == -1) return;

	InvenMgr->AddItem(ItemID);
	AddGachaLog(ItemID);

	OnGachaCompleted.Broadcast();
}

void UPopupGachaVM::OnGachaMulti(const int32 InItemCount)
{
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);

	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	const TArray<int32> ItemIDs = GachaMgr->GetGachaItemMultiple(InItemCount);
	if (ItemIDs.IsEmpty()) return;

	InvenMgr->AddItems(ItemIDs);
	for (const int32 ID : ItemIDs)
	{
		AddGachaLog(ID);
	}

	OnGachaCompleted.Broadcast();
}

void UPopupGachaVM::AddGachaLog(const int32 InItemID)
{
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);

	UTableManager* TableMgr = GetTableManager();
	VALID_RETURN(TableMgr);

	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);

	const FItemTableData* TableData = TableMgr->GetItemTableData(InItemID);
	if (!TableData) return;

	FGachaLogData Data;
	Data.ItemName   = TableData->ItemName;
	Data.GradeColor = UIMgr->GetItemColor(TableData->ItemGrade);
	Data.Time       = FDateTime::Now().ToString(TEXT("%H:%M:%S"));

	GachaMgr->AddLog(Data);
}
