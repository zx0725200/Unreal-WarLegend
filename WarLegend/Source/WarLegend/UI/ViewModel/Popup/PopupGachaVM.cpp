#include "PopupGachaVM.h"

#include "GachaManager.h"
#include "InventoryManager.h"
#include "ETC/Define.h"

void UPopupGachaVM::Init()
{
	Super::Init();
}

void UPopupGachaVM::OnGacha(const int32 InItemCount)
{
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);

	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);

	const TArray<int32> ItemIDs = GachaMgr->GetGachaItemMultiple(InItemCount);
	if (ItemIDs.IsEmpty()) return;

	InvenMgr->AddItems(ItemIDs);
	for (const int32 ID : ItemIDs)
	{
		AddGachaLog(ID);
	}

	OnGachaCompleted.Broadcast();
}

void UPopupGachaVM::AddGachaLog(const int32 InItemID)
{
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);
	
	GachaMgr->AddLog(InItemID);
}
