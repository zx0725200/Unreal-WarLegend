// Fill out your copyright notice in the Description page of Project Settings.


#include "GachaPresenter.h"

#include "DataManager/GachaManager.h"
#include "DataManager/InventoryManager.h"
#include "DataManager/SaveGameDataManager.h"
#include "DataManager/TableManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Kismet/GameplayStatics.h"
#include "Popup/PopupGacha.h"
#include "Popup/PopupGachaFilter.h"
#include "ViewModel/Popup/PopupGachaFilterVM.h"
#include "ViewModel/Popup/PopupGachaVM.h"
#include "Popup/PopupGachaLog.h"
#include "ViewModel/Popup/PopupGachaLogVM.h"

void UGachaPresenter::Init(UUIManagerImpl* InUIMgr)
{
	// UIMgr    = InUIMgr;
	//
	// UGameInstance* GI = UGameplayStatics::GetGameInstance(UIMgr);
	// GachaMgr    = GI->GetSubsystem<UGachaManager>();
	// SaveGameMgr = GI->GetSubsystem<USaveGameDataManager>();
	// TableMgr	= GI->GetSubsystem<UTableManager>();
	//
	// ULocalPlayer* LP = GI->GetFirstGamePlayer();
	// InvenMgr = LP->GetSubsystem<UInventoryManager>();
	//
	// GachaLogVM = NewObject<UPopupGachaLogVM>(this);
	//
	// GachaMgr->ApplyFilter();
}

void UGachaPresenter::OpenPopupGacha()
{
	// if (!UIMgr || !GachaMgr || !InvenMgr || !TableMgr) return;
	//
	// auto* GachaPopup = UIMgr->ShowUI<UPopupGacha>(TEXT("PopupGacha"));
	// if (!GachaPopup) return;
	//
	// UPopupGachaVM* VM = NewObject<UPopupGachaVM>(GachaPopup);
	// VM->Init();
	// VM->GetOnToastRequested().AddUObject(this, &UGachaPresenter::HandleShowToast); 
	//
	//GachaPopup->SetViewModel(VM);
}

void UGachaPresenter::OpenPopupGachaFilter()
{
	if (!UIMgr || !SaveGameMgr || !GachaMgr) return;

	auto* FilterPopup = UIMgr->ShowUI<UPopupGachaFilter>(TEXT("PopupGachaFilter"));
	if (!FilterPopup) return;
	
	UPopupGachaFilterVM* VM = NewObject<UPopupGachaFilterVM>(FilterPopup);
	VM->Init();
	
	FilterPopup->SetViewModel(VM);
}

void UGachaPresenter::OpenPopupGachaLog()
{
	// if (!UIMgr) return;
	//
	// auto* PopupGachaLog = UIMgr->ShowUI<UPopupGachaLog>(TEXT("PopupGachaLog"),ESlateVisibility::SelfHitTestInvisible);
	// if (!PopupGachaLog) return;
	//
	// PopupGachaLog->SetViewModel(GachaLogVM);
	// PopupGachaLog->ShowAsFull();
}

void UGachaPresenter::HandleShowToast()
{
	// auto* PopupLog = UIMgr->ShowUI<UPopupGachaLog>(TEXT("PopupGachaLog"),ESlateVisibility::SelfHitTestInvisible);
	// if (!PopupLog) return;
	//
	// PopupLog->SetViewModel(GachaLogVM);
	// PopupLog->ShowAsToast();
}
