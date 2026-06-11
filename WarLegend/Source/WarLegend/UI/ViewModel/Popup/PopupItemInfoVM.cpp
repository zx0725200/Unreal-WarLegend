// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupItemInfoVM.h"

#include "InventoryManager.h"
#include "ETC/Define.h"

void UPopupItemInfoVM::Init()
{
	Super::Init();

	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	SelectedItemData = InvenMgr->GetSelectedItemData();

	RefreshEquippedData();
}

void UPopupItemInfoVM::OnEquip()
{
	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	InvenMgr->EquipItem(SelectedItemData.UniqueID);

	RefreshEquippedData();
}

int32 UPopupItemInfoVM::GetHPDiff() const
{
	return SelectedItemData.HP - (bHasEquippedItem ? EquippedItemData.HP : 0);
}

int32 UPopupItemInfoVM::GetATKDiff() const
{
	return SelectedItemData.ATK - (bHasEquippedItem ? EquippedItemData.ATK : 0);
}

int32 UPopupItemInfoVM::GetDEFDiff() const
{
	return SelectedItemData.DEF - (bHasEquippedItem ? EquippedItemData.DEF : 0);
}

void UPopupItemInfoVM::RefreshEquippedData()
{
	bHasEquippedItem = false;
	bSelectedEquipped = false;
	EquippedItemData = FMyItem();

	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	const FMyItem* Equipped = InvenMgr->FindEquippedItemData(SelectedItemData.ItemType);
	if (!Equipped)
	{
		return;
	}

	EquippedItemData = *Equipped;
	bHasEquippedItem = true;
	bSelectedEquipped = Equipped->UniqueID == SelectedItemData.UniqueID;
}
