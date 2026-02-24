// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenInventory.h"

#include "Components/VerticalBox.h"
#include "ETC/Define.h"
#include "Slot/SlotEquipItem.h"
#include "ViewModel/Screen/ScreenInventoryVM.h"

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
	Vertical_Equip->ClearChildren();
	for (const auto& EquipItem : VM->LeftItemTypes)
	{
		USlotEquipItem* SlotEquipItem = CreateWidget<USlotEquipItem>(GetWorld(), EquipSlotClass);
		VALID_RETURN(SlotEquipItem);
		
		Vertical_Equip->AddChild(SlotEquipItem);
	}
	
	Vertical_Boss->ClearChildren();
	for (const auto& Boss : VM->RightItemTypes)
	{
		USlotEquipItem* SlotBossItem = CreateWidget<USlotEquipItem>(GetWorld(), EquipSlotClass);
		VALID_RETURN(SlotBossItem);
		
		Vertical_Boss->AddChild(SlotBossItem);
	}
}
