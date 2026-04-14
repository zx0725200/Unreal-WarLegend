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
	
	Btn_Exit->SetVisibility(ESlateVisibility::Visible);
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
}

void UPopupGachaLog::ShowAsToast()
{
	if (!VM) return;
	
	CreateLogSlot();
	ApplyDisplayMode(EGachaLogDisplayMode::Toast);
}

void UPopupGachaLog::ShowAsFull()
{
	if (!VM) return;
	
	ApplyDisplayMode(EGachaLogDisplayMode::Full);
}

void UPopupGachaLog::StartHideTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(HideTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &UPopupGachaLog::StartHide, 3.0f, false);
}

void UPopupGachaLog::ApplyDisplayMode(const EGachaLogDisplayMode InMode)
{
	const bool bToast = (InMode == EGachaLogDisplayMode::Toast);
	
	SB_Log->ScrollToEnd();
	
	Btn_Exit->SetVisibility(bToast ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	
	GetWorld()->GetTimerManager().ClearTimer(HideTimerHandle);
	
	if (!bToast)
	{
		return;
	}
	
	StartHideTimer();
}

void UPopupGachaLog::CreateLogSlot() const
{
	const auto& LogList = VM->GetLogList();
	const auto& LastData = LogList.Last();
	
	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	if (!UIMgr) return;

	auto* LogSlot = UIMgr->CreateSlot<USlotGachaLog>(TEXT("SlotGachaLog"), SB_Log);
	LogSlot->Init(LastData);
}

void UPopupGachaLog::OnClickedClear()
{
	if (!VM)
	{
		return;
	}
	
	VM->ClearAll();
}
