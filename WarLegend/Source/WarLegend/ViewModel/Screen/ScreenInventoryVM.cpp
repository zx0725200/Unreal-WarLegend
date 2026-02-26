// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenInventoryVM.h"

const TArray<TObjectPtr<USlotInventoryVM>>& UScreenInventoryVM::GetItems() const
{
	check(InvenMgr); 
	return InvenMgr->GetInventoryItemData(); 
}
