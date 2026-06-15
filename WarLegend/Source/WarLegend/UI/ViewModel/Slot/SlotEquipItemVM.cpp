// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotEquipItemVM.h"

#include "UIManagerImpl.h"
#include "DataManager/InventoryManager.h"
#include "ETC/Define.h"
#include "ETC/Struct.h"

void USlotEquipItemVM::SetItemType(const EItemType InItemType)
{
	ItemType = InItemType;
}

bool USlotEquipItemVM::HasEquipped() const
{
	return FindEquipped() != nullptr;
}

FString USlotEquipItemVM::GetEquippedName() const
{
	const FMyItem* Equipped = FindEquipped();
	return Equipped ? Equipped->ItemName : FString();
}

FLinearColor USlotEquipItemVM::GetEquippedColor() const
{
	const FMyItem* Equipped = FindEquipped();
	return Equipped ? Equipped->ItemGradeColor : FLinearColor::White;
}

void USlotEquipItemVM::OnClickedSlot()
{
	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	// 빈 슬롯이면 보여줄 정보가 없으니 무시한다.
	const FMyItem* Equipped = InvenMgr->FindEquippedItemData(ItemType);
	if (!Equipped)
	{
		return;
	}

	InvenMgr->SetSelectedItem(Equipped->UniqueID);

	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);

	UIMgr->ShowUI(TEXT("PopupItemInfo"));
}

const FMyItem* USlotEquipItemVM::FindEquipped() const
{
	const UInventoryManager* InvenMgr = GetInvenManager();
	if (!InvenMgr)
	{
		return nullptr;
	}

	return InvenMgr->FindEquippedItemData(ItemType);
}
