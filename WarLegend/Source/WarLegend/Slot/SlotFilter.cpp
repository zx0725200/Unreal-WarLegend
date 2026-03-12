// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotFilter.h"

#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "ViewModel/Slot/SlotFilterVM.h"

void USlotFilter::Awake()
{
	Super::Awake();
	
	ChBox_Filter->OnCheckStateChanged.AddDynamic(this, &USlotFilter::OnCheckBoxChanged);
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
	
	SetData();
}

void USlotFilter::SetData()
{
	if (!VM) return;
	
	Txt_Filter->SetText(FText::FromString(VM->GradeName));
	ChBox_Filter->SetIsChecked(VM->bChecked);
}

void USlotFilter::OnCheckBoxChanged(const bool bIsChecked)
{
	if (!VM) return;

	VM->bChecked = bIsChecked;
	VM->OnFilterChanged.Broadcast(VM->Grade, bIsChecked);
}
