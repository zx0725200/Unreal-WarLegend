#include "SlotInventoryVM.h"
#include "UIManagerImpl.h"
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
	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);
	
	UIMgr->ShowUI(TEXT("PopupItemInfo"));
}
