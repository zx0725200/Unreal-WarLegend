#include "SlotDungeonMenu.h"
#include "Components/TextBlock.h"
#include "Slot/SlotDungeonVM.h"

void USlotDungeonMenu::Awake()
{
	Super::Awake();
}

void USlotDungeonMenu::OnEnable()
{
	Super::OnEnable();
}

void USlotDungeonMenu::OnDisable()
{
	Super::OnDisable();
	VM = nullptr;
}

void USlotDungeonMenu::OnClickEvent(const FName& InChildName)
{
	VALID_RETURN(VM);
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Dungeon"))
	{
		VM->OnEnterDungeon();
	}
}

void USlotDungeonMenu::SetData(USlotDungeonVM* InData)
{
	VALID_RETURN(InData);
	
	VM = InData;
	
	const FDungeonTableData& Data = VM->GetData();
	RefreshName(Data.DungeonName);
	RefreshLevel(Data.MinLevel, Data.MaxLevel);
}

void USlotDungeonMenu::RefreshName(const FString& InName) const
{
	Txt_Name->SetText(FText::FromString(InName));
}

void USlotDungeonMenu::RefreshLevel(const int32 InMin, const int32 InMax) const
{
	const FString LevelText = FString::Printf(TEXT("Lv.%d ~ %d"), InMin, InMax);
	Txt_Level->SetText(FText::FromString(LevelText));
}
