// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupItemInfoVM.h"

#include "InventoryManager.h"
#include "ETC/Define.h"
#include "ViewModel/Slot/SlotItemInfoVM.h"

void UPopupItemInfoVM::Init()
{
	Super::Init();

	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	SelectedItemData = InvenMgr->GetSelectedItemData();

	RefreshEquippedData();
	BuildSlotVMs();
}

void UPopupItemInfoVM::OnEquip()
{
	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	InvenMgr->EquipItem(SelectedItemData.UniqueID);

	RefreshEquippedData();
}

void UPopupItemInfoVM::OnUnequip()
{
	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	InvenMgr->UnequipItem(SelectedItemData.ItemType);

	RefreshEquippedData();
}

int32 UPopupItemInfoVM::GetHPDiff() const
{
	return SelectedItemData.HP - (HasEquippedItem() ? EquippedItemData.HP : 0);
}

int32 UPopupItemInfoVM::GetATKDiff() const
{
	return SelectedItemData.ATK - (HasEquippedItem() ? EquippedItemData.ATK : 0);
}

int32 UPopupItemInfoVM::GetDEFDiff() const
{
	return SelectedItemData.DEF - (HasEquippedItem() ? EquippedItemData.DEF : 0);
}

void UPopupItemInfoVM::RefreshEquippedData()
{
	EquipState = EEquipCompareState::NoEquipped;
	EquippedItemData = FMyItem();

	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	const FMyItem* Equipped = InvenMgr->FindEquippedItemData(SelectedItemData.ItemType);
	if (!Equipped)
	{
		return;
	}

	EquippedItemData = *Equipped;
	EquipState = (Equipped->UniqueID == SelectedItemData.UniqueID)
		? EEquipCompareState::SelfEquipped
		: EEquipCompareState::OtherEquipped;
}

void UPopupItemInfoVM::BuildSlotVMs()
{
	// 선택 슬롯: 장착 중이면 "장착중", 아니면 장착템과 비교
	SelectedSlotVM = NewObject<USlotItemInfoVM>(this);
	SelectedSlotVM->SetItem(SelectedItemData);

	if (IsSelectedEquipped())
	{
		SelectedSlotVM->SetEquipped();
	}
	else
	{
		SelectedSlotVM->SetCompare(GetHPDiff(), GetATKDiff(), GetDEFDiff());
	}

	// 비교 대상(현재 장착) 슬롯: 항상 "장착중"
	EquippedSlotVM = NewObject<USlotItemInfoVM>(this);
	EquippedSlotVM->SetItem(EquippedItemData);
	EquippedSlotVM->SetEquipped();
}
