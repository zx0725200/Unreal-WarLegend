#include "ScreenInventoryVM.h"
#include "DataManager/InventoryManager.h"
#include "DataManager/TableManager.h"
#include "DataManager/UIManagerImpl.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "ViewModel/Slot/SlotInventoryVM.h"

void UScreenInventoryVM::Init()
{
	Super::Init();
	
	UTableManager* TableMgr = GetTableManager();
	VALID_RETURN(TableMgr);
	
	for (const EItemType ItemType : GetTableManager()->GetLeftEquipTypes())
	{
		LeftItemTypes.Emplace(ItemType, TableMgr->GetItemTypeName(ItemType));
	}
		
	for (const EItemType ItemType : TableMgr->GetRightEquipTypes())
	{
		RightItemTypes.Emplace(ItemType, TableMgr->GetItemTypeName(ItemType));
	}
	
	AddItemList();
}

void UScreenInventoryVM::AddItemList()
{
	ItemList.Empty();
    
	const auto InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);
	
	for (const FMyItem& MyItem : InvenMgr->GetInventoryItemData())
	{
		// 장착 중인 아이템은 인벤토리 목록에서 숨긴다 (장착 슬롯에만 표시).
		if (InvenMgr->IsEquippedItem(MyItem.UniqueID))
		{
			continue;
		}

		USlotInventoryVM* SlotVM = NewObject<USlotInventoryVM>(this);
		SlotVM->SetData(MyItem);
		ItemList.Emplace(SlotVM);
	}

	// 새로 목록을 만든 뒤에도 현재 정렬 순서를 유지한다.
	SortItemList();
}

void UScreenInventoryVM::SortItemList()
{
	const bool bAscending = (SortOrder == ESortOrder::Ascending);

	ItemList.Sort([bAscending](const TObjectPtr<USlotInventoryVM>& A, const TObjectPtr<USlotInventoryVM>& B)
	{
		const FMyItem& ItemA = A->GetMyItem();
		const FMyItem& ItemB = B->GetMyItem();

		// 1차: 등급순
		if (ItemA.ItemGrade != ItemB.ItemGrade)
		{
			const uint8 GradeA = static_cast<uint8>(ItemA.ItemGrade);
			const uint8 GradeB = static_cast<uint8>(ItemB.ItemGrade);
			return bAscending ? GradeA < GradeB : GradeA > GradeB;
		}

		// 2차: 같은 등급이면 스탯 합계순
		const int32 TotalA = ItemA.GetTotalStat();
		const int32 TotalB = ItemB.GetTotalStat();

		return bAscending ? TotalA < TotalB : TotalA > TotalB;
	});
}

void UScreenInventoryVM::ToggleSort()
{
	SortOrder = (SortOrder == ESortOrder::Ascending) ? ESortOrder::Descending : ESortOrder::Ascending;
	SortItemList();
}

void UScreenInventoryVM::OnReset()
{
	const auto InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	InvenMgr->ResetItem();
}

void UScreenInventoryVM::RefreshItems()
{
	AddItemList();
}

void UScreenInventoryVM::DiscardByFilter()
{
	const auto InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	InvenMgr->DiscardItemsByFilter();

	AddItemList();
}

void UScreenInventoryVM::OpenDiscardSetting()
{
	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);

	UIMgr->ShowUI(TEXT("PopupItemDiscard"));
}

FEquipStatTotal UScreenInventoryVM::GetEquippedStatTotal() const
{
	const auto InvenMgr = GetInvenManager();
	if (!InvenMgr)
	{
		return FEquipStatTotal();
	}

	return InvenMgr->GetEquippedStatTotal();
}
