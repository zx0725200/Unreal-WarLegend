#include "SlotFilterVM.h"

#include "GachaManager.h"
#include "SaveGameDataManager.h"
#include "ETC/Define.h"

void USlotFilterVM::Init(const EItemGrade InGrade, const FString& InName, const FLinearColor& InColor, const bool InChecked)
{
	Grade = InGrade;
	GradeName = InName;
	GradeColor = InColor;
	bChecked = InChecked;
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
	
	UGachaManager* GachaMgr = GetGachaManager();
	VALID_RETURN(GachaMgr);
	
	SaveGameMgr->SetGachaFilter(InGrade, InChecked);
	GachaMgr->ApplyFilter();
}
