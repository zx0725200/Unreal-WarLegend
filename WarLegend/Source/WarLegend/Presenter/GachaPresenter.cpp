// Fill out your copyright notice in the Description page of Project Settings.


#include "GachaPresenter.h"

#include "DataAsset/WLSaveGame.h"
#include "DataManager/GachaManager.h"
#include "DataManager/InventoryManager.h"
#include "DataManager/SaveGameDataManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Popup/PopupGacha.h"
#include "Popup/PopupGachaFilter.h"
#include "ViewModel/Popup/PopupGachaFilterVM.h"
#include "ViewModel/Popup/PopupGachaVM.h"
#include "ViewModel/Slot/SlotFilterVM.h"
#include "ETC/Constant.h" 

void UGachaPresenter::Init(UUIManagerImpl* InUIMgr, UGachaManager* InGachaMgr, UInventoryManager* InInvenMgr, USaveGameDataManager* InSaveGameMgr)
{
	UIMgr    = InUIMgr;
	GachaMgr = InGachaMgr;
	InvenMgr = InInvenMgr;
	SaveGameMgr = InSaveGameMgr;
	
	ApplyFilter();
}

void UGachaPresenter::OpenPopupGacha()
{
	if (!UIMgr || !GachaMgr || !InvenMgr) return;

	auto* GachaPopup = UIMgr->ShowUI<UPopupGacha>(TEXT("PopupGacha"));
	if (!GachaPopup) return;

	UPopupGachaVM* VM = NewObject<UPopupGachaVM>(GachaPopup);
	VM->OnClickOne.AddUObject(this, &UGachaPresenter::HandleClickOne);
	VM->OnClickTen.AddUObject(this, &UGachaPresenter::HandleClickTen);
	VM->OnClickAll.AddUObject(this, &UGachaPresenter::HandleClickAll);

	GachaPopup->SetViewModel(VM);
}

void UGachaPresenter::OpenPopupGachaFilter()
{
	if (!UIMgr || !SaveGameMgr) return;

	auto* FilterPopup = UIMgr->ShowUI<UPopupGachaFilter>(TEXT("PopupGachaFilter"));
	if (!FilterPopup) return;

	UWLSaveGame* Save = SaveGameMgr->GetSaveGame();
	if (!Save) return;

	UPopupGachaFilterVM* VM = NewObject<UPopupGachaFilterVM>(FilterPopup);

	// Epic 제외한 등급 순서대로 슬롯 VM 생성
	const TArray<TPair<EItemGrade, FString>> GradeList =
	{
		{ EItemGrade::Normal, TEXT("Normal") },
		{ EItemGrade::Rare,   TEXT("Rare")   },
		{ EItemGrade::Unique, TEXT("Unique") },
		{ EItemGrade::Legend, TEXT("Legend") },
	};

	for (const auto& [Grade, Name] : GradeList)
	{
		USlotFilterVM* SlotVM = NewObject<USlotFilterVM>(VM);
		SlotVM->Grade     = Grade;
		SlotVM->GradeName = Name;
		SlotVM->GradeColor= UIMgr->GetItemColor(Grade);
		SlotVM->bChecked  = Save->GachaFilter.FindRef(Grade); // 저장된 값 복원
		SlotVM->OnFilterChanged.AddUObject(this, &UGachaPresenter::HandleFilterChanged);

		VM->SlotVMList.Emplace(SlotVM);
	}
	
	FilterPopup->SetViewModel(VM);
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

void UGachaPresenter::HandleClickOne()
{
	if (!GachaMgr || !InvenMgr) return;

	const int32 ItemID = GachaMgr->GetGachaItem();
	InvenMgr->AddItem(ItemID);
}

void UGachaPresenter::HandleClickTen()
{
	if (!GachaMgr || !InvenMgr) return;

	constexpr int32 TenItems = 10;
	const TArray<int32> ItemIDs = GachaMgr->GetGachaItemMultiple(TenItems);
	InvenMgr->AddItems(ItemIDs);
}

void UGachaPresenter::HandleClickAll()
{
	if (!GachaMgr || !InvenMgr) return;

	// 수정 예정
	constexpr int32 MaxItems = 30;
	const TArray<int32> ItemIDs = GachaMgr->GetGachaItemMultiple(MaxItems);
	InvenMgr->AddItems(ItemIDs);
}

void UGachaPresenter::HandleFilterChanged(EItemGrade Grade, bool bChecked)
{
	if (!SaveGameMgr) return;
 
	UWLSaveGame* SaveData = SaveGameMgr->GetSaveGame();
	if (!SaveData) return;
 
	SaveData->GachaFilter.Add(Grade, bChecked);
	SaveGameMgr->SaveGame(Constant::SaveData);
	
	ApplyFilter();
}
