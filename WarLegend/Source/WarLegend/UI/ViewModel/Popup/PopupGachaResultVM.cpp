// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaResultVM.h"

#include "GachaManager.h"
#include "ETC/Define.h"
#include "ViewModel/Slot/SlotGachaResultVM.h"

void UPopupGachaResultVM::Init()
{
	Super::Init();

	BuildResultSlots();
}

void UPopupGachaResultVM::OnRetry()
{
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);

	// 직전 뽑기와 같은 개수로 다시 뽑는다(결과 개수 = 직전 뽑기 개수). PullGacha 이후 LastResults가 갱신되므로 먼저 캐싱.
	const int32 RetryCount = GachaMgr->GetLastResults().Num();
	if (RetryCount <= 0) return;

	if (!GachaMgr->PullGacha(RetryCount)) return;

	BuildResultSlots(); // 새 결과로 슬롯 VM 리스트 재구성
}

void UPopupGachaResultVM::BuildResultSlots()
{
	ItemList.Empty();

	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);

	int32 RevealOrder = 0;
	for (const FGachaLogData& Data : GachaMgr->GetLastResults())
	{
		USlotGachaResultVM* SlotVM = NewObject<USlotGachaResultVM>(this);
		SlotVM->SetData(Data, RevealOrder++); // 나온 순서대로 연출 인덱스 부여
		ItemList.Emplace(SlotVM);
	}
}
