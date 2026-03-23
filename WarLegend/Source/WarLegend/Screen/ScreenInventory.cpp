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
	
	if (InChildName == TEXT("Btn_Reset"))
	{
		OnClickedReset();
	}
}

void UScreenInventory::SetViewModel(UScreenInventoryVM* InData)
{
	VM = InData;
	
	Init();
}

void UScreenInventory::Init()
{
	InitEquipSlots();
	InitInventorySlots();
}

void UScreenInventory::InitEquipSlots()
{
	CreateEquipSlots(Vertical_Equip, VM->GetLeftItemTypes());
	CreateEquipSlots(Vertical_Boss, VM->GetLightItemTypes());
}

void UScreenInventory::InitInventorySlots()
{
	TileView_Inventory->ClearListItems();
	for (const auto& HavingItem : VM->GetItems())
	{
		TileView_Inventory->AddItem(HavingItem);
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

void UScreenInventory::OnClickedReset()
{
	if (!VM)
	{
		return;
	}
	
	TileView_Inventory->ClearListItems();
	VM->HandleReset();
}
