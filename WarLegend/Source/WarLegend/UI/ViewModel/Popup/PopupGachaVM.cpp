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

	InvenMgr->AddItems(ItemIDs); // 분해(-1)는 내부에서 스킵된다.
	for (const int32 ID : ItemIDs)
	{
		if (ID == -1) continue; // 분해된 결과는 로그/인벤에 남기지 않는다.
		GachaMgr->AddLog(ID);
	}

	GachaMgr->RecordResults(ItemIDs); // 결과 팝업은 분해 포함 뽑은 개수 전부 표시

	OnGachaCompleted.Broadcast();
}
