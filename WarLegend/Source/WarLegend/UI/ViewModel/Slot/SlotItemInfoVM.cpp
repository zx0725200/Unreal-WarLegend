// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotItemInfoVM.h"

void USlotItemInfoVM::SetItem(const FMyItem& InItem)
{
	ItemData = InItem;
}

void USlotItemInfoVM::SetCompare(const int32 InHPDiff, const int32 InATKDiff, const int32 InDEFDiff)
{
	HPDiff = InHPDiff;
	ATKDiff = InATKDiff;
	DEFDiff = InDEFDiff;
	Mode = EItemInfoMode::Compare;
}

void USlotItemInfoVM::SetEquipped()
{
	Mode = EItemInfoMode::Equipped;
}
