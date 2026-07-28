#include "PopupGachaVM.h"

#include "GachaManager.h"
#include "InventoryManager.h"
#include "UIManagerImpl.h"
#include "ETC/Define.h"

void UPopupGachaVM::Init()
{
	Super::Init();
}

void UPopupGachaVM::OnGacha(const int32 InItemCount)
{
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);

	if (!GachaMgr->PullGacha(InItemCount)) return;

	ShowGachaResult();
}

void UPopupGachaVM::ShowGachaResult() const
{
	const auto UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);

	UIMgr->ShowUI(TEXT("PopupGachaResult"));
}
