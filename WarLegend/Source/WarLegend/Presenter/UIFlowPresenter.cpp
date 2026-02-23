// Fill out your copyright notice in the Description page of Project Settings.


#include "UIFlowPresenter.h"

#include "DataManager/TableManager.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "DataTable/DungeonTableData.h"
#include "ETC/Define.h"
#include "Popup/PopupDungeonMenu.h"
#include "Screen/ScreenInventory.h"
#include "Screen/ScreenTitle.h"
#include "ViewModel/Popup/PopupDungeonMenuVM.h"
#include "ViewModel/Screen/ScreenTitleVM.h"

void UUIFlowPresenter::OpenScreenTitle()
{
	auto* UIMgr = GTGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	if (const auto ScreenTitle = UIMgr->ShowUI<UScreenTitle>(TEXT("ScreenTitle")))
	{
		UScreenTitleVM* TitleData = NewObject<UScreenTitleVM>(ScreenTitle);
		
		TitleData->OnConfirmRequested.RemoveAll(this);
		TitleData->OnConfirmRequested.AddUObject(this, &UUIFlowPresenter::HandleTitleConfirm);
		
		ScreenTitle->SetViewModel(TitleData);
	}
}

void UUIFlowPresenter::OpenScreenInventory()
{
	const auto* GI = GetWorld()->GetGameInstance();
	if (!GI) return;
	
	auto* TableMgr = GI->GetSubsystem<UTableManager>();
	if (!TableMgr) return;
	
	auto* UIMgr = GTGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	if (auto* ScreenInventory = UIMgr->ShowUI<UScreenInventory>(TEXT("ScreenInventory")))
	{
		ScreenInventory->SetViewModel();
	}
}

void UUIFlowPresenter::OpenPopupDungeonMenu()
{
	const auto* GI = GetWorld()->GetGameInstance();
	if (!GI) return;

	auto* TableMgr = GI->GetSubsystem<UTableManager>();
	if (!TableMgr) return;

	auto* UIMgr = GTGetMgrImpl(UIManager);
	if (!UIMgr) return;

	const auto DungeonTableDataList = TableMgr->GetDungeonTableData();
	if (DungeonTableDataList.IsEmpty()) return;
	
	TArray<UPopupDungeonMenuVM*> DungeonDataList;
	DungeonDataList.Reserve(DungeonTableDataList.Num());
	
	for (const auto& DungeonData : DungeonTableDataList)
	{
		UPopupDungeonMenuVM* InDungeonData = NewObject<UPopupDungeonMenuVM>(this);
		InDungeonData->ID = DungeonData->DungeonID;
		InDungeonData->Name = DungeonData->DungeonName;
		InDungeonData->MinLevel = DungeonData->MinLevel;
		InDungeonData->MaxLevel = DungeonData->MaxLevel;
		
		InDungeonData->OnConfirmRequested.RemoveAll(this);
		InDungeonData->OnConfirmRequested.AddUObject(this, &UUIFlowPresenter::HandleSlotDungeonMenuClick);
		
		DungeonDataList.Emplace(InDungeonData);
	}
	
	if (auto* Popup = UIMgr->ShowUI<UPopupDungeonMenu>(TEXT("PopupDungeonMenu")))
	{
		Popup->SetViewModel(DungeonDataList);
		Popup->Init();
	}
}

void UUIFlowPresenter::HandleTitleConfirm()
{
	auto* UIMgr = GTGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	UIMgr->ShowUI<UScreenTitle>(TEXT("HudPlayerState"));
}

void UUIFlowPresenter::HandleSlotDungeonMenuClick(int32 InSlotIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Start Pos Change %d"), InSlotIndex);
}

