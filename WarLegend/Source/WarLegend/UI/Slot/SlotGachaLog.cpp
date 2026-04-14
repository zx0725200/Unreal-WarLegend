// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotGachaLog.h"

#include "Components/TextBlock.h"
#include "ETC/Struct.h"

void USlotGachaLog::Init(const FGachaLogData& InData)
{
	const auto ItemName = FText::FromString(InData.ItemName);
	const auto ItemColor = InData.GradeColor;
	const auto ItemTime = FText::FromString(InData.Time);
	
	Txt_ItemName->SetText(ItemName);
	Txt_ItemName->SetColorAndOpacity(ItemColor);
	
	Txt_Time->SetText(ItemTime);
}
