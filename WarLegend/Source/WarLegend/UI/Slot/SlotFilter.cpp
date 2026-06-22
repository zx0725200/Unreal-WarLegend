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

void USlotFilter::SetData(USlotFilterVM* InVM)
{
	VALID_RETURN(InVM);
	VM = InVM;
	
	RefreshFilter();
}

void USlotFilter::RefreshFilter()
{
	VALID_RETURN(VM);
	
	const FText GradeName = FText::FromString(VM->GetGradeName());
	const auto GradeColor = VM->GetGradeColor();
	const auto FilterCheck = VM->IsChecked();
	
	Txt_Filter->SetText(GradeName);
	Txt_Filter->SetColorAndOpacity(GradeColor);
	ChBox_Filter->SetIsChecked(FilterCheck);
}

void USlotFilter::OnCheckBoxChanged(const bool bIsChecked)
{
	VALID_RETURN(VM);
	
	VM->SetChecked(bIsChecked);
}
