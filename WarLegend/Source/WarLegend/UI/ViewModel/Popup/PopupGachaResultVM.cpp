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
