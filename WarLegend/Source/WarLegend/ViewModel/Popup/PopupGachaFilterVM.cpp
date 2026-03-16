// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaFilterVM.h"

#include "DataAsset/WLSaveGame.h"
#include "DataManager/UIManagerImpl.h"
#include "ETC/Enum.h"
#include "ViewModel/Slot/SlotFilterVM.h"

void UPopupGachaFilterVM::Init(const UUIManagerImpl* InUIMgr, const UWLSaveGame* InSaveData)
{
	const TArray<TPair<EItemGrade, FString>> GradeList =
	{
		{ EItemGrade::Normal, TEXT("Normal") },
		{ EItemGrade::Rare,   TEXT("Rare")   },
		{ EItemGrade::Unique, TEXT("Unique") },
		{ EItemGrade::Legend, TEXT("Legend") },
	};

	for (const auto& [Grade, Name] : GradeList)
	{
		USlotFilterVM* SlotVM = NewObject<USlotFilterVM>(this);
		const auto ItemColor = InUIMgr->GetItemColor(Grade);
		const auto bItemChecked = InSaveData->GachaFilter.FindRef(Grade);
		SlotVM->Init(Grade, Name, ItemColor, bItemChecked);
		SlotVMList.Emplace(SlotVM);
	}
}

void UPopupGachaFilterVM::BroadCastConfirm()
{
	OnConfirm.Broadcast();
}
