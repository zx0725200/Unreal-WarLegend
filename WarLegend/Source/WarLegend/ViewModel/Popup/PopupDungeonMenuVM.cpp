// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupDungeonMenuVM.h"

#include "DataManager/DungeonManager.h"
#include "DataManager/UIManagerImpl.h"

void UPopupDungeonMenuVM::Init(UDungeonManager* InDungeonMgr, UUIManagerImpl* InUIMgr)
{
	DungeonMgr = InDungeonMgr;
	UIMgr = InUIMgr;
}

void UPopupDungeonMenuVM::SetName(const FString& InName)
{
	Name = InName;
	OnNameChanged.Broadcast(Name);
}

void UPopupDungeonMenuVM::SetLevel(const int32 InMin, const int32 InMax)
{
	MinLevel = InMin;
	MaxLevel = InMax;
	OnLevelChanged.Broadcast(MinLevel, MaxLevel);
}

void UPopupDungeonMenuVM::SetID(const int32 InID)
{
	ID = InID;
}

void UPopupDungeonMenuVM::BroadCastEnterDungeon()
{
	if (!DungeonMgr || !UIMgr) return;
	DungeonMgr->EnterDungeon(ID);
	UIMgr->HideUI(TEXT("PopupDungeonMenu"));
}

void UPopupDungeonMenuVM::BroadCastExitDungeon()
{
	if (!DungeonMgr) return;
	DungeonMgr->ExitDungeon();
}
