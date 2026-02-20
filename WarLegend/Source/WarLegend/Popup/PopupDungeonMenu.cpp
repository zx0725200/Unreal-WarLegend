// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupDungeonMenu.h"
#include "Components/VerticalBox.h"
#include "Slot/SlotDungeonMenu.h"
#include "ETC/Define.h"

void UPopupDungeonMenu::Awake()
{
	Super::Awake();
}

void UPopupDungeonMenu::OnEnable()
{
	Super::OnEnable();
}

void UPopupDungeonMenu::OnDisable()
{
	Super::OnDisable();
}

void UPopupDungeonMenu::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
}

void UPopupDungeonMenu::Init(const TArray<UPopupDungeonMenuVM*>& InData)
{
	if (DungeonSlots.Num() >= InData.Num())
	{
		// TODO: 리프레시 코드 추가
		return;
	}
	
	for (const auto& DungeonData : InData)
	{
		USlotDungeonMenu* DungeonMenu = CreateWidget<USlotDungeonMenu>(GetWorld(), SlotClass);
		VALID_RETURN(DungeonMenu);
		
		DungeonMenu->SetData(DungeonData);
		
		Vertical_DungeonMenu->AddChild(DungeonMenu);
		DungeonSlots.Add(DungeonMenu);
	}
}
