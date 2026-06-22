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
	
	RefreshName();
	RefreshLevel();
}

void USlotDungeonMenu::RefreshName() const
{
	const FString DungeonName = VM->GetData().DungeonName;
	Txt_Name->SetText(FText::FromString(DungeonName));
}

void USlotDungeonMenu::RefreshLevel() const
{
	const int32 MinLevel = VM->GetData().MinLevel;
	const int32 MaxLevel = VM->GetData().MaxLevel;
	
	const FString LevelText = FString::Printf(TEXT("Lv.%d ~ %d"), MinLevel, MaxLevel);
	Txt_Level->SetText(FText::FromString(LevelText));
}
