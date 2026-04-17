#include "PopupDungeonMenuVM.h"
#include "TableManager.h"
#include "DataTable/DungeonTableData.h"
#include "ETC/Constant.h"
#include "ETC/Define.h"
#include "Slot/SlotDungeonVM.h"

void UPopupDungeonMenuVM::Init()
{
	Super::Init();
	
	UTableManager* TableMgr = GetTableManager();
	VALID_RETURN(TableMgr);
	
	const auto DungeonList = TableMgr->GetAllDungeonTableData();
	if (DungeonList.IsEmpty())
	{
		return;
	}
	
	SlotDungeonVMList.Reset();
	SlotDungeonVMList.Reserve(DungeonList.Num());

	for (const auto& Data : DungeonList)
	{
		USlotDungeonVM* VM = NewObject<USlotDungeonVM>(this);
		VM->Init(*Data);
		
		SlotDungeonVMList.Emplace(VM);
	}
	
	CurrentPageIndex = 1;
}

void UPopupDungeonMenuVM::NotifyAll()
{
	Super::NotifyAll();
	
	OnPageChanged.Broadcast(GetCurrentSlotList(), CurrentPageIndex, GetMaxPage());
}

void UPopupDungeonMenuVM::OnNextPage()
{
	OnChangePage(CurrentPageIndex + 1);
}

void UPopupDungeonMenuVM::OnPrevPage()
{
	OnChangePage(CurrentPageIndex - 1);
}

void UPopupDungeonMenuVM::OnChangePage(int32 NewPage)
{
	const int32 MaxPage = GetMaxPage();
	NewPage = FMath::Clamp(NewPage, 1, MaxPage);

	if (CurrentPageIndex == NewPage) return;

	CurrentPageIndex = NewPage;
	OnPageChanged.Broadcast(GetCurrentSlotList(), CurrentPageIndex, MaxPage);
}

TArray<USlotDungeonVM*> UPopupDungeonMenuVM::GetCurrentSlotList() const
{
	TArray<USlotDungeonVM*> SlotList;
	const int32 Start = (CurrentPageIndex - 1) * Constant::PageSize;
	for (int32 i = 0; i < Constant::PageSize; ++i)
	{
		if (SlotDungeonVMList.IsValidIndex(Start + i))
		{
			SlotList.Add(SlotDungeonVMList[Start + i]);
		}
	}
	
	return SlotList;
}

int32 UPopupDungeonMenuVM::GetMaxPage() const
{
	const int32 Raw = FMath::DivideAndRoundUp(SlotDungeonVMList.Num(), Constant::PageSize);
	return FMath::Max(Raw, 1);
}
