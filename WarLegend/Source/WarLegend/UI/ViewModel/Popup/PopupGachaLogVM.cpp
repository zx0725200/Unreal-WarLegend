#include "PopupGachaLogVM.h"

#include "GachaManager.h"
#include "ETC/Define.h"

void UPopupGachaLogVM::Init()
{
	Super::Init();

	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);

	GachaMgr->GetOnLogAdded().AddUObject(this, &UPopupGachaLogVM::HandleLogAdded);
	GachaMgr->GetOnLogCleared().AddUObject(this, &UPopupGachaLogVM::HandleLogCleared);
}

void UPopupGachaLogVM::NotifyAll()
{
	Super::NotifyAll();

	OnLogCleared.Broadcast();

	for (const FGachaLogData& Data : GetLogList())
	{
		OnLogAdded.Broadcast(Data);
	}
}

void UPopupGachaLogVM::ClearBinding()
{
	Super::ClearBinding();

	if (UGachaManager* GachaMgr = GetGachaManager())
	{
		GachaMgr->GetOnLogAdded().RemoveAll(this);
		GachaMgr->GetOnLogCleared().RemoveAll(this);
	}
}

void UPopupGachaLogVM::ClearAll()
{
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);

	GachaMgr->ClearLogs();
}

const TArray<FGachaLogData>& UPopupGachaLogVM::GetLogList() const
{
	const TArray<FGachaLogData> Empty;

	const UGachaManager* GachaMgr = GetGachaManager();
	return GachaMgr ? GachaMgr->GetLogList() : Empty;
}

void UPopupGachaLogVM::HandleLogAdded(const FGachaLogData& InData)
{
	OnLogAdded.Broadcast(InData);
}

void UPopupGachaLogVM::HandleLogCleared()
{
	OnLogCleared.Broadcast();
}
