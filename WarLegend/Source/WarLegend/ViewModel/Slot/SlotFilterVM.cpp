// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotFilterVM.h"

void USlotFilterVM::Init(const EItemGrade InGrade, const FString& InName, const FLinearColor& InColor, const bool InChecked)
{
	Grade = InGrade;
	GradeName = InName;
	GradeColor = InColor;
	bChecked = InChecked;
}

void USlotFilterVM::SetChecked(const bool InChecked)
{
	bChecked = InChecked;
	OnFilterChanged.Broadcast(Grade, bChecked);
}
