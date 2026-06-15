#include "SlotInventoryVM.h"
#include "UIManagerImpl.h"
#include "DataManager/InventoryManager.h"
#include "ETC/Define.h"

void USlotInventoryVM::Init()
{
	Super::Init();
}

void USlotInventoryVM::SetData(const FMyItem& InData)
{
	MyItem = InData;
}

void USlotInventoryVM::OnOpenItemInfo(const FMyItem& InData)
{
	// 팝업이 어떤 아이템을 보여줄지 매니저에 기록해둔다.
	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	InvenMgr->SetSelectedItem(InData.UniqueID);

	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);

	UIMgr->ShowUI(TEXT("PopupItemInfo"));
}

bool USlotInventoryVM::IsUpgrade() const
{
	// 업그레이드 판정은 매니저가 책임진다.
	const UInventoryManager* InvenMgr = GetInvenManager();
	if (!InvenMgr)
	{
		return false;
	}

	return InvenMgr->IsUpgrade(MyItem);
}
