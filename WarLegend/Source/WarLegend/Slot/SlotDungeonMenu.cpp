// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotDungeonMenu.h"

#include "Components/TextBlock.h"
#include "DataTable/DungeonTableData.h"
#include "ViewModel/PopupDungeonMenuVM.h"

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
}

void USlotDungeonMenu::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Dungeon"))
	{
		VM->Confirm();
	}
}

void USlotDungeonMenu::SetData(UPopupDungeonMenuVM* InData)
{
	VM = InData;
	
	SetDungeonName();
}

void USlotDungeonMenu::SetDungeonName()
{
	const FText DungeonNameText = FText::FromString(VM->Name);
	
	FString LevelString = TEXT("레벨");
	LevelString += FString::Printf(TEXT("%d~%d"),VM->MinLevel, VM->MaxLevel);
	
	const FText DungeonLevelText = FText::FromString(LevelString);
	
	Txt_Name->SetText(DungeonNameText);
	Txt_Level->SetText(DungeonLevelText);
}
