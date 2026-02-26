// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"

#include "ViewModel/Slot/SlotInventoryVM.h"

void UInventoryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	for (int32 i=0; i<10; i++)
	{
		USlotInventoryVM* SlotInventoryVM = NewObject<USlotInventoryVM>(this);
		SlotInventoryVM->ID = i;
	
		InventoryItemData.Emplace(SlotInventoryVM);
	}
}
