// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotFilter.h"

#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "ViewModel/Slot/SlotFilterVM.h"

void USlotFilter::Awake()
{
	Super::Awake();
}

void USlotFilter::OnEnable()
{
	Super::OnEnable();
}

void USlotFilter::OnDisable()
{
	Super::OnDisable();
}

void USlotFilter::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
}

void USlotFilter::SetViewModel(USlotFilterVM* InVM)
{
	VM = InVM;
	if (!VM) return;

	SetData();
}

void USlotFilter::SetData()
{
	if (Txt_Filter)
	{
		Txt_Filter->SetText(FText::FromString(VM->GradeName));
	}

	if (ChBox_Filter)
	{
		ChBox_Filter->SetIsChecked(VM->bChecked);
	}
}

void USlotFilter::OnCheckBoxChanged(const bool bIsChecked)
{
	if (!VM) return;

	VM->bChecked = bIsChecked;
	VM->OnFilterChanged.Broadcast(VM->Grade, bIsChecked);
}
