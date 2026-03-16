// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaLog.h"

#include "Components/ScrollBox.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Slot/SlotGachaLog.h"
#include "ViewModel/Popup/PopupGachaLogVM.h"

void UPopupGachaLog::Awake()
{
	Super::Awake();
}

void UPopupGachaLog::OnEnable()
{
	Super::OnEnable();
}

void UPopupGachaLog::OnDisable()
{
	Super::OnDisable();
}

void UPopupGachaLog::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	if (InChildName == TEXT("Btn_Clear"))
	{
		OnClickedClear();
	}
}

void UPopupGachaLog::StartHide()
{
	Super::Hide();
}

void UPopupGachaLog::SetViewModel(UPopupGachaLogVM* InVM)
{
	if (VM == InVM) return;

	if (VM)
	{
		VM->GetOnLogUpdated().RemoveAll(this);
		VM->GetOnLogCleared().RemoveAll(this);
	}
	
	VM = InVM;
	VM->GetOnLogUpdated().AddUObject(this, &UPopupGachaLog::HandleLogUpdated);
	VM->GetOnLogCleared().AddUObject(this, &UPopupGachaLog::HandleLogCleared);
}

void UPopupGachaLog::RefreshAll()
{
	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	SB_Log->ClearChildren();
	for (const auto& LogData : VM->GetLogList())
	{
		auto* GachaLogSlot = UIMgr->CreateSlot<USlotGachaLog>(TEXT("SlotGachaLog"), SB_Log);
		GachaLogSlot->Init(LogData);
	}
	SB_Log->ScrollToEnd();
}

void UPopupGachaLog::OnClickedClear()
{
	if (!VM) return;
	VM->ClearAll();
}

void UPopupGachaLog::HandleLogUpdated()
{
	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	const auto& LogList = VM->GetLogList();
	const auto& Last = LogList.Last();
	
	auto* GachaLogSlot = UIMgr->CreateSlot<USlotGachaLog>(TEXT("SlotGachaLog"), SB_Log);
	GachaLogSlot->Init(Last);
	
	StartAutoHide();
	SB_Log->ScrollToEnd();
}

void UPopupGachaLog::HandleLogCleared()
{
	SB_Log->ClearChildren();
}

void UPopupGachaLog::StartAutoHide()
{
	GetWorld()->GetTimerManager().ClearTimer(HideTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &UPopupGachaLog::StartHide, 5.0f, false);
}
