// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotInventory.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ETC/Struct.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "ViewModel/Slot/SlotInventoryVM.h"

void USlotInventory::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	VM = Cast<USlotInventoryVM>(ListItemObject);
	
	SetNormalState();
	SetData();
	
	EVENT_LISTEN(TEXT("SelectItem"), FMyItem, this, &ThisClass::HandleClickedSlot);
}

void USlotInventory::NativeDestruct()
{
	Super::NativeDestruct();
}

void USlotInventory::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Slot"))
	{
		OnClickedSlot();
	}
}

void USlotInventory::SetData() const
{
	const auto ItemColor = VM->ItemGradeColor;
	const FText ItemName = FText::FromString(VM->ItemName);
	const FText ItemTypeName = FText::FromString(VM->ItemTypeName);
	
	Txt_Grade->SetText(ItemTypeName);
	Txt_Grade->SetColorAndOpacity(ItemColor);
	
	Txt_Name->SetText(ItemName);
	Txt_Name->SetColorAndOpacity(ItemColor);
}

void USlotInventory::OnClickedSlot()
{
	FMyItem MyItem;
	MyItem.Name = TEXT("SelectItem");
	MyItem.ID = VM->ID;
		
	EVENT_BROADCAST(MyItem.Name, FMyItem, this, MyItem);
}

void USlotInventory::SetSelectedState()
{
	Img_Select->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Img_NotSelect->SetVisibility(ESlateVisibility::Collapsed);
}

void USlotInventory::SetNormalState()
{
	Img_Select->SetVisibility(ESlateVisibility::Collapsed);
	Img_NotSelect->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void USlotInventory::HandleClickedSlot(FGameplayTag InTag, const FMyItem& InItem)
{
	if (InItem.ID == VM->ID)
	{
		SetSelectedState();
	}
	else
	{
		SetNormalState();
	}
}
