// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotDungeonVM.h"

#include "DungeonManager.h"
#include "UIManagerImpl.h"
#include "ETC/Define.h"

void USlotDungeonVM::Init(const FDungeonTableData& InData)
{
	Data = InData;
}

void USlotDungeonVM::OnEnterDungeon()
{
	UDungeonManager* DungeonMgr = GetDungeonManager();
	VALID_RETURN(DungeonMgr);

	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);

	DungeonMgr->EnterDungeon(Data.DungeonID);
	UIMgr->HideUI(TEXT("PopupDungeonMenu"));
}

void USlotDungeonVM::OnExitDungeon()
{
	UDungeonManager* DungeonMgr = GetDungeonManager();
	VALID_RETURN(DungeonMgr);

	DungeonMgr->ExitDungeon();
}
