#include "PopupItemDiscardVM.h"

#include "DataAsset/WLSaveGame.h"
#include "DataManager/SaveGameDataManager.h"
#include "DataManager/UIManagerImpl.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "ViewModel/Slot/SlotFilterVM.h"

void UPopupItemDiscardVM::Init()
{
	Super::Init();

	USaveGameDataManager* SaveGameDataMgr = GetSaveGameDataManager();
	VALID_RETURN(SaveGameDataMgr);

	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);

	UWLSaveGame* SaveData = SaveGameDataMgr->GetSaveGame();
	VALID_RETURN(SaveData);

	const TArray<TPair<EItemGrade, FString>> GradeList =
	{
		{ EItemGrade::Normal, TEXT("Normal") },
		{ EItemGrade::Rare,   TEXT("Rare")   },
		{ EItemGrade::Unique, TEXT("Unique") },
		{ EItemGrade::Legend, TEXT("Legend") },
		{ EItemGrade::Epic,   TEXT("Epic")   },
	};

	for (const auto& [Grade, Name] : GradeList)
	{
		USlotFilterVM* SlotVM = NewObject<USlotFilterVM>(this);
		const auto ItemColor = UIMgr->GetItemColor(Grade);
		const auto bItemChecked = SaveData->DiscardFilter.FindRef(Grade);

		SlotVM->Init(Grade, Name, ItemColor, bItemChecked, EFilterType::Discard);

		SlotVMList.Emplace(SlotVM);
	}
}

void UPopupItemDiscardVM::NotifyAll()
{
	Super::NotifyAll();

	OnSlotListChanged.Broadcast(SlotVMList);
}
