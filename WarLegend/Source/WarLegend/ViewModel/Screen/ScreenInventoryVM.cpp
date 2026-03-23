// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenInventoryVM.h"

#include "DataManager/InventoryManager.h"
#include "DataManager/TableManager.h"
#include "ViewModel/Slot/SlotInventoryVM.h"

void UScreenInventoryVM::Init(UInventoryManager* InMgr, UTableManager* InTableMgr)
{
	InvenMgr = InMgr;
	
	for (const EItemType ItemType : InTableMgr->GetLeftEquipTypes())
	{
		LeftItemTypes.Emplace(ItemType, InTableMgr->GetItemTypeName(ItemType));
	}
		
	for (const EItemType ItemType : InTableMgr->GetRightEquipTypes())
	{
		RightItemTypes.Emplace(ItemType, InTableMgr->GetItemTypeName(ItemType));
	}
	
	RefreshItems();
}

void UScreenInventoryVM::RefreshItems()
{
	Items.Empty();
    
	for (const FMyItem& MyItem : InvenMgr->GetInventoryItemData())
	{
		USlotInventoryVM* SlotVM = NewObject<USlotInventoryVM>(this);
		SlotVM->Init(MyItem);
		SlotVM->GetOnItemInfoRequested().AddUObject(this, &UScreenInventoryVM::HandleOpenItemInfo);
		Items.Emplace(SlotVM);
	}
}

void UScreenInventoryVM::HandleReset()
{
	if (!InvenMgr)
	{
		return;
	}
	
	InvenMgr->ResetItem();
}

void UScreenInventoryVM::HandleOpenItemInfo(const FMyItem& InItem)
{
	OnItemInfoRequested.Broadcast(InItem);
}

const TArray<TObjectPtr<USlotInventoryVM>>& UScreenInventoryVM::GetItems() const
{
	return Items;
}

const TMap<EItemType, FString>& UScreenInventoryVM::GetLeftItemTypes() const
{
	return LeftItemTypes;
}

const TMap<EItemType, FString>& UScreenInventoryVM::GetLightItemTypes() const
{
	return RightItemTypes;
}
