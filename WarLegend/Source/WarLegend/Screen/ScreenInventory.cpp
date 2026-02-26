// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenInventory.h"

#include "Components/TileView.h"
#include "Components/VerticalBox.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "Slot/SlotEquipItem.h"
#include "ViewModel/Screen/ScreenInventoryVM.h"
#include "ViewModel/Slot/SlotInventoryVM.h"

void UScreenInventory::Awake()
{
	Super::Awake();
}

void UScreenInventory::OnEnable()
{
	Super::OnEnable();
}

void UScreenInventory::OnDisable()
{
	Super::OnDisable();
}

void UScreenInventory::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
}

void UScreenInventory::SetViewModel(UScreenInventoryVM* InData)
{
	VM = InData;
}

void UScreenInventory::Init()
{
	InitEquipSlots();
	InitInventorySlots();
}

void UScreenInventory::InitEquipSlots()
{
	CreateEquipSlots(Vertical_Equip, VM->LeftItemTypes);
	CreateEquipSlots(Vertical_Boss, VM->RightItemTypes);
}

void UScreenInventory::InitInventorySlots()
{
	for (const auto& HavingItem : VM->GetItems())
	{
		for (int32 i=0; i <50; i++)
		{
			TileView_Inventory->AddItem(HavingItem);
		}
	}
}

void UScreenInventory::CreateEquipSlots(UVerticalBox* InParent, const TMap<EItemType, FString>& InItemData) const
{
	InParent->ClearChildren();
	for (const auto& EquipItem : InItemData)
	{
		USlotEquipItem* SlotEquipItem = CreateWidget<USlotEquipItem>(GetWorld(), EquipSlotClass);
		VALID_RETURN(SlotEquipItem);
		
		SlotEquipItem->SetData(EquipItem.Key, EquipItem.Value);
		
		InParent->AddChild(SlotEquipItem);
	}
}
