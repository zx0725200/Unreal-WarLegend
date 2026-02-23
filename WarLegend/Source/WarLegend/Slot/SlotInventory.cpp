// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotInventory.h"

void USlotInventory::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
}
