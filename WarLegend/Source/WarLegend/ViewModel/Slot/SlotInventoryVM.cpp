// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotInventoryVM.h"

void USlotInventoryVM::Init(const FMyItem& InData)
{
	MyItem = InData;
}

void USlotInventoryVM::OpenPopupItemInfo()
{
	OnItemInfoRequested.Broadcast(MyItem);
	
}
