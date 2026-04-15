#include "PopupGachaFilterVM.h"

#include "DataAsset/WLSaveGame.h"
#include "DataManager/SaveGameDataManager.h"
#include "DataManager/UIManagerImpl.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "ViewModel/Slot/SlotFilterVM.h"

void UPopupGachaFilterVM::Init()
{
	Super::Init();
	
	USaveGameDataManager* SaveGameDataMgr = GetSaveGameDataManager();
	VALID_RETURN(SaveGameDataMgr);
	
	UUIManagerImpl* UIMgr  = GetUIManager();
	VALID_RETURN(SaveGameDataMgr);
	
	UWLSaveGame* SaveData = SaveGameDataMgr->GetSaveGame();
	VALID_RETURN(SaveData);
	
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
		const auto ItemColor = UIMgr->GetItemColor(Grade);
		const auto bItemChecked = SaveData->GachaFilter.FindRef(Grade);
		
		SlotVM->Init(Grade, Name, ItemColor, bItemChecked);
		
		SlotVMList.Emplace(SlotVM);
	}
}
