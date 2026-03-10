// Fill out your copyright notice in the Description page of Project Settings.


#include "GachaPresenter.h"

#include "DataManager/GachaManager.h"
#include "DataManager/InventoryManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Popup/PopupGacha.h"
#include "ViewModel/Popup/PopupGachaVM.h"

void UGachaPresenter::Init(UUIManagerImpl* InUIMgr, UGachaManager* InGachaMgr, UInventoryManager* InInvenMgr)
{
	UIMgr    = InUIMgr;
	GachaMgr = InGachaMgr;
	InvenMgr = InInvenMgr;
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
