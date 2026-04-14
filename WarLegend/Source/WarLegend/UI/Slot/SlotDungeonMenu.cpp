// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotDungeonMenu.h"
#include "Components/TextBlock.h"
#include "ViewModel/Popup/PopupDungeonMenuVM.h"

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
		if (!VM) return;
		VM->BroadCastEnterDungeon();
	}
}

void USlotDungeonMenu::SetData(UPopupDungeonMenuVM* InData)
{
	if (!InData) return;
	
	VM = InData;
	
	// 이벤트 등록
	AddVmEvent();
	
	// 초기 값 설정
	RefreshName(VM->GetDungeonName());
	RefreshLevel(VM->GetMinLevel(), VM->GetMaxLevel());
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

void USlotDungeonMenu::AddVmEvent()
{
	if (!VM) return;
	
	VM->GetOnNameChanged().RemoveAll(this);
	VM->GetOnLevelChanged().RemoveAll(this);
	
	VM->GetOnNameChanged().AddUObject(this, &USlotDungeonMenu::RefreshName);
	VM->GetOnLevelChanged().AddUObject(this, &USlotDungeonMenu::RefreshLevel);
}
