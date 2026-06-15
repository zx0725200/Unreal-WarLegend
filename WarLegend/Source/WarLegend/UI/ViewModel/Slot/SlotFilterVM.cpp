#include "SlotFilterVM.h"

#include "GachaManager.h"
#include "SaveGameDataManager.h"
#include "ETC/Define.h"

void USlotFilterVM::Init(const EItemGrade InGrade, const FString& InName, const FLinearColor& InColor, const bool InChecked, const EFilterType InFilterType)
{
	Grade = InGrade;
	GradeName = InName;
	GradeColor = InColor;
	bChecked = InChecked;
	FilterType = InFilterType;
}

void USlotFilterVM::SetChecked(const bool InChecked)
{
	bChecked = InChecked;
	OnFilterChanged(Grade, bChecked);
}

void USlotFilterVM::OnFilterChanged(const EItemGrade InGrade, const bool InChecked)
{
	USaveGameDataManager* SaveGameMgr = GetSaveGameDataManager();
	VALID_RETURN(SaveGameMgr);

	// 버리기 필터는 가챠와 무관하게 세이브에만 기록한다.
	if (FilterType == EFilterType::Discard)
	{
		SaveGameMgr->SetDiscardFilter(InGrade, InChecked);
		return;
	}

	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);

	SaveGameMgr->SetGachaFilter(InGrade, InChecked);
	GachaMgr->ApplyFilter();
}
