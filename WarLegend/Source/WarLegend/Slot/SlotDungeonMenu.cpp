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
}

void USlotDungeonMenu::SetData(const UPopupDungeonMenuVM* InData)
{
	SetDungeonName(InData);
}

void USlotDungeonMenu::SetDungeonName(const UPopupDungeonMenuVM* InData)
{
	const FText DungeonNameText = FText::FromString(InData->Name);
	
	FString LevelString = TEXT("레벨");
	LevelString += FString::Printf(TEXT("%d~%d"),InData->MinLevel, InData->MaxLevel);
	
	const FText DungeonLevelText = FText::FromString(LevelString);
	
	Txt_Name->SetText(DungeonNameText);
	Txt_Level->SetText(DungeonLevelText);
}
