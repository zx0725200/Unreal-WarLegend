// Fill out your copyright notice in the Description page of Project Settings.


#include "GachaPresenter.h"

#include "DataAsset/WLSaveGame.h"
#include "DataManager/GachaManager.h"
#include "DataManager/InventoryManager.h"
#include "DataManager/SaveGameDataManager.h"
#include "DataManager/TableManager.h"
#include "DataManager/UIManagerImpl.h"
#include "DataTable/ItemTableData.h"
#include "Popup/PopupGacha.h"
#include "Popup/PopupGachaFilter.h"
#include "ViewModel/Popup/PopupGachaFilterVM.h"
#include "ViewModel/Popup/PopupGachaVM.h"
#include "ViewModel/Slot/SlotFilterVM.h"
#include "ETC/Struct.h"
#include "Popup/PopupGachaLog.h"
#include "ViewModel/Popup/PopupGachaLogVM.h"

void UGachaPresenter::Init(UUIManagerImpl* InUIMgr, UGachaManager* InGachaMgr, UInventoryManager* InInvenMgr, USaveGameDataManager* InSaveGameMgr, UTableManager* InTableMgr)
{
	UIMgr    = InUIMgr;
	GachaMgr = InGachaMgr;
	InvenMgr = InInvenMgr;
	SaveGameMgr = InSaveGameMgr;
	TableMgr = InTableMgr;
	
	GachaLogVM = NewObject<UPopupGachaLogVM>(this);
	
	ApplyFilter();
}

void UGachaPresenter::OpenPopupGacha()
{
	if (!UIMgr || !GachaMgr || !InvenMgr) return;

	auto* GachaPopup = UIMgr->ShowUI<UPopupGacha>(TEXT("PopupGacha"));
	if (!GachaPopup) return;

	UPopupGachaVM* VM = NewObject<UPopupGachaVM>(GachaPopup);
	VM->GetOnClickOne().AddUObject(this, &UGachaPresenter::HandleClickOne);
	VM->GetOnClickTen().AddUObject(this, &UGachaPresenter::HandleClickTen);
	VM->GetOnClickAll().AddUObject(this, &UGachaPresenter::HandleClickAll);

	GachaPopup->SetViewModel(VM);
}

void UGachaPresenter::OpenPopupGachaFilter()
{
	if (!UIMgr || !SaveGameMgr) return;

	auto* FilterPopup = UIMgr->ShowUI<UPopupGachaFilter>(TEXT("PopupGachaFilter"));
	if (!FilterPopup) return;

	UWLSaveGame* SaveData = SaveGameMgr->GetSaveGame();
	if (!SaveData) return;

	UPopupGachaFilterVM* VM = NewObject<UPopupGachaFilterVM>(FilterPopup);
	VM->Init(UIMgr, SaveData);

	for (const auto& SlotVM : VM->GetSlotVMList())
	{
		SlotVM->GetOnFilterChanged().AddUObject(this, &UGachaPresenter::HandleFilterChanged);
	}
	
	FilterPopup->SetViewModel(VM);
}

void UGachaPresenter::OpenPopupGachaLog()
{
	if (!UIMgr) return;
	
	const auto PopupGachaLog = UIMgr->ShowUI<UPopupGachaLog>(TEXT("PopupGachaLog"));
	if (!PopupGachaLog) return;
	
	PopupGachaLog->SetViewModel(GachaLogVM);
	PopupGachaLog->RefreshAll();
}

void UGachaPresenter::ApplyFilter() const
{
	if (!GachaMgr || !SaveGameMgr) return;

	UWLSaveGame* Save = SaveGameMgr->GetSaveGame();
	if (!Save) return;

	TArray<EItemGrade> AllowedGrades;
	for (const auto& [Grade, bChecked] : Save->GachaFilter)
	{
		if (!bChecked) continue;
		AllowedGrades.Emplace(Grade);
	}

	GachaMgr->SetFilter(AllowedGrades);
}

void UGachaPresenter::ShowToast_Gacha(const int32 InItemID)
{
	if (!UIMgr) return;
	
	const auto* TableData = TableMgr->GetItemTableData(InItemID);
	if (!TableData) return;
	
	const auto PopupGachaLog = UIMgr->ShowUI<UPopupGachaLog>(TEXT("PopupGachaLog"));
	if (!PopupGachaLog) return;
	
	PopupGachaLog->SetViewModel(GachaLogVM);
	
	FGachaLogData GachaLogData;
	GachaLogData.ItemName   = TableData->ItemName;
	GachaLogData.GradeColor = UIMgr->GetItemColor(TableData->ItemGrade);
	GachaLogData.Time       = FDateTime::Now().ToString(TEXT("%H:%M:%S"));
	
	GachaLogVM->AddLog(GachaLogData);
}

void UGachaPresenter::ShowToast_MultiGacha(const TArray<int32>& InItemList)
{
	for (const auto& ItemID : InItemList)
	{
		ShowToast_Gacha(ItemID);
	}
}

void UGachaPresenter::HandleClickOne()
{
	if (!GachaMgr || !InvenMgr) return;

	const int32 ItemID = GachaMgr->GetGachaItem();
	if (ItemID == -1) return;
	
	InvenMgr->AddItem(ItemID);
	ShowToast_Gacha(ItemID);
}

void UGachaPresenter::HandleClickTen()
{
	if (!GachaMgr || !InvenMgr) return;

	constexpr int32 TenItems = 10;
	const TArray<int32> ItemIDs = GachaMgr->GetGachaItemMultiple(TenItems);
	
	InvenMgr->AddItems(ItemIDs);
	ShowToast_MultiGacha(ItemIDs);
}

void UGachaPresenter::HandleClickAll()
{
	if (!GachaMgr || !InvenMgr) return;

	// 수정 예정
	constexpr int32 MaxItems = 30;
	const TArray<int32> ItemIDs = GachaMgr->GetGachaItemMultiple(MaxItems);
	InvenMgr->AddItems(ItemIDs);
	
	ShowToast_MultiGacha(ItemIDs);
}

void UGachaPresenter::HandleFilterChanged(const EItemGrade InGrade, const bool bChecked)
{
	if (!SaveGameMgr) return;
	SaveGameMgr->SetGachaFilter(InGrade, bChecked);
	
	ApplyFilter();
}
