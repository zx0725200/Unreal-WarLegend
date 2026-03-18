// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaFilterVM.h"

#include "DataAsset/WLSaveGame.h"
#include "DataManager/GachaManager.h"
#include "DataManager/SaveGameDataManager.h"
#include "DataManager/UIManagerImpl.h"
#include "ETC/Enum.h"
#include "ViewModel/Slot/SlotFilterVM.h"

void UPopupGachaFilterVM::Init(const UUIManagerImpl* InUIMgr, USaveGameDataManager* InSaveGameMgr, UGachaManager* InGachaMgr)
{
	SaveGameMgr = InSaveGameMgr;
	GachaMgr    = InGachaMgr;
	
	UWLSaveGame* SaveData = SaveGameMgr->GetSaveGame();
	if (!SaveData) return;
	
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
		const auto bItemChecked = SaveData->GachaFilter.FindRef(Grade);
		
		SlotVM->Init(Grade, Name, ItemColor, bItemChecked);
		SlotVM->GetOnFilterChanged().AddUObject(this, &UPopupGachaFilterVM::HandleFilterChanged); 
		
		SlotVMList.Emplace(SlotVM);
	}
}

void UPopupGachaFilterVM::HandleFilterChanged(const EItemGrade InGrade, const bool bChecked)
{
	if (!SaveGameMgr || !GachaMgr) return;
	SaveGameMgr->SetGachaFilter(InGrade, bChecked);
	GachaMgr->ApplyFilter();
}
