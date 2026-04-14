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
	if (!VM) return;

	VBox_Filter->ClearChildren();

	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	const auto SlotList = VM->GetSlotVMList();
	if (SlotList.IsEmpty()) return;
	
	for (USlotFilterVM* SlotVM : SlotList)
	{
		if (!SlotVM) continue;

		USlotFilter* SlotWidget = UIMgr->CreateSlot<USlotFilter>(TEXT("SlotFilter"), VBox_Filter);
		SlotWidget->SetViewModel(SlotVM);
	}
}
