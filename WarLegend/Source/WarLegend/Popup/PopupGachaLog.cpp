// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaLog.h"

#include "Components/ScrollBox.h"
#include "Core/UMyButton.h"
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
	VM = InVM;
	
	AddEvent();
	
	Btn_Exit->SetVisibility(ESlateVisibility::Visible);
}

void UPopupGachaLog::AddEvent()
{
	if (!VM) return;
	
	VM->GetOnLogUpdated().RemoveAll(this);
	VM->GetOnLogCleared().RemoveAll(this);
	
	VM->GetOnLogUpdated().AddUObject(this, &UPopupGachaLog::HandleLogUpdated);
	VM->GetOnLogCleared().AddUObject(this, &UPopupGachaLog::HandleLogCleared);
}

void UPopupGachaLog::StartHideTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(HideTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &UPopupGachaLog::StartHide, 3.0f, false);
}

void UPopupGachaLog::CreateLogSlot(const FGachaLogData& InLogData) const
{
	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	if (!UIMgr) return;

	auto* LogSlot = UIMgr->CreateSlot<USlotGachaLog>(TEXT("SlotGachaLog"), SB_Log);
	LogSlot->Init(InLogData);
}

void UPopupGachaLog::OnClickedClear()
{
	if (!VM) return;
	VM->ClearAll();
}

void UPopupGachaLog::HandleLogUpdated()
{
	const auto& LogList = VM->GetLogList();
	const auto& LastData = LogList.Last();
	
	CreateLogSlot(LastData);
	
	StartHideTimer();
	SB_Log->ScrollToEnd();
	Btn_Exit->SetVisibility(ESlateVisibility::Collapsed);
}

void UPopupGachaLog::HandleLogCleared()
{
	SB_Log->ClearChildren();
}
