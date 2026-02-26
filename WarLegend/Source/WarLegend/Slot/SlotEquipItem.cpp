// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotEquipItem.h"

#include "Components/TextBlock.h"

void USlotEquipItem::Awake()
{
	Super::Awake();
}

void USlotEquipItem::OnEnable()
{
	Super::OnEnable();
}

void USlotEquipItem::OnDisable()
{
	Super::OnDisable();
}

void USlotEquipItem::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
}

void USlotEquipItem::SetData(const EItemType InItemType, const FString& InItemName)
{
	Txt_Name->SetText(FText::FromString(InItemName));
}