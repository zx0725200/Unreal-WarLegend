// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonPresenter.h"
#include "DataManager/DungeonManager.h"
#include "DataManager/TableManager.h"
#include "DataManager/UIManagerImpl.h"
#include "DataTable/DungeonTableData.h"
#include "Popup/PopupDungeonMenu.h"
#include "ViewModel/Popup/PopupDungeonMenuVM.h"


void UDungeonPresenter::Init(UUIManagerImpl* InUIMgr, UTableManager* InTableMgr, UDungeonManager* InDungeonMgr)
{
	UIMgr    = InUIMgr;
	TableMgr = InTableMgr;
	DungeonMgr = InDungeonMgr;
}

void UDungeonPresenter::OpenPopupDungeonMenu()
{
	if (!UIMgr || !TableMgr) return;
	
	const auto DungeonList = TableMgr->GetAllDungeonTableData();
	if (DungeonList.IsEmpty()) return;

	auto* DungeonPopup = UIMgr->ShowUI<UPopupDungeonMenu>(TEXT("PopupDungeonMenu"));
	if (!DungeonPopup) return;
	
	VMList.Reset();
	VMList.Reserve(DungeonList.Num());

	for (const auto& Data : DungeonList)
	{
		UPopupDungeonMenuVM* VM = NewObject<UPopupDungeonMenuVM>(DungeonPopup);
		VM->Init();
		VM->SetID(Data->DungeonID);
		VM->SetName(Data->DungeonName);
		VM->SetLevel(Data->MinLevel, Data->MaxLevel);
		
		VMList.Emplace(VM);
	}

	// Widget에 넘기면 → Widget 내부에서 VM 이벤트 구독
	// 이후 VM 데이터 바뀌면 Widget이 알아서 갱신
	DungeonPopup->SetViewModel(VMList);
	DungeonPopup->Init();
}
