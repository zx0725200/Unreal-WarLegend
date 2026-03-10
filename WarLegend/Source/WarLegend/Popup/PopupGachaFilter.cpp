// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaFilter.h"

#include "Components/VerticalBox.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Slot/SlotFilter.h"
#include "ViewModel/Popup/PopupGachaFilterVM.h"
#include "ViewModel/Slot/SlotFilterVM.h"

void UPopupGachaFilter::Awake()
{
	Super::Awake();
}

void UPopupGachaFilter::OnEnable()
{
	Super::OnEnable();
}

void UPopupGachaFilter::OnDisable()
{
	Super::OnDisable();
	VM = nullptr;
}

void UPopupGachaFilter::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
}

void UPopupGachaFilter::SetViewModel(UPopupGachaFilterVM* InVM)
{
	VM = InVM;
	RefreshSlots();
}

void UPopupGachaFilter::RefreshSlots()
{
	if (!VM || !VerticalBox_Slots) return;

	VerticalBox_Slots->ClearChildren();

	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	for (USlotFilterVM* SlotVM : VM->SlotVMList)
	{
		if (!SlotVM) continue;

		USlotFilter* SlotWidget = UIMgr->CreateSlot<USlotFilter>(TEXT("SlotFilter"), VerticalBox_Slots);
		if (!SlotWidget) continue;
		
		SlotWidget->SetViewModel(SlotVM);
	}
}
