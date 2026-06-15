// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotEquipItem.h"

#include "Components/TextBlock.h"
#include "ETC/Define.h"
#include "ETC/Struct.h"
#include "ViewModel/Slot/SlotEquipItemVM.h"

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

	if (InChildName == TEXT("Btn_Slot"))
	{
		OnClickedSlot();
	}
}

void USlotEquipItem::OnClickedSlot()
{
	VALID_RETURN(VM);

	VM->OnClickedSlot();
}

void USlotEquipItem::SetData(const EItemType InItemType, const FString& InItemName)
{
	VM = NewObject<USlotEquipItemVM>(this);
	VM->SetItemType(InItemType);

	Txt_Name->SetText(FText::FromString(InItemName));

	RefreshEquipped();

	EVENT_LISTEN(TEXT("EquipChanged"), FMyItem, this, &ThisClass::HandleEquipChanged);
}

void USlotEquipItem::RefreshEquipped() const
{
	VALID_RETURN(VM, Txt_ItemName);

	if (VM->HasEquipped())
	{
		Txt_ItemName->SetText(FText::FromString(VM->GetEquippedName()));
		Txt_ItemName->SetColorAndOpacity(VM->GetEquippedColor());
	}
	else
	{
		Txt_ItemName->SetText(FText::FromString(TEXT("비어있음")));
		Txt_ItemName->SetColorAndOpacity(FLinearColor(0.6f, 0.6f, 0.6f));
	}
}

void USlotEquipItem::HandleEquipChanged(FGameplayTag InTag, const FMyItem& InItem)
{
	VALID_RETURN(VM);

	// 내 타입의 장착이 바뀌었을 때만 갱신
	if (InItem.ItemType != VM->GetItemType())
	{
		return;
	}

	RefreshEquipped();
}
