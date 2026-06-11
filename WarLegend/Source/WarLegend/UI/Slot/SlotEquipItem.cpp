// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotEquipItem.h"

#include "Components/TextBlock.h"
#include "DataManager/InventoryManager.h"
#include "ETC/Define.h"
#include "ETC/Struct.h"

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
	MyItemType = InItemType;

	Txt_Name->SetText(FText::FromString(InItemName));

	RefreshEquipped();

	EVENT_LISTEN(TEXT("EquipChanged"), FMyItem, this, &ThisClass::HandleEquipChanged);
}

void USlotEquipItem::RefreshEquipped() const
{
	VALID_RETURN(Txt_ItemName);

	UInventoryManager* InvenMgr = GTUIGetMgr(UInventoryManager);
	VALID_RETURN(InvenMgr);

	if (const FMyItem* Equipped = InvenMgr->FindEquippedItemData(MyItemType))
	{
		Txt_ItemName->SetText(FText::FromString(Equipped->ItemName));
		Txt_ItemName->SetColorAndOpacity(Equipped->ItemGradeColor);
	}
	else
	{
		Txt_ItemName->SetText(FText::FromString(TEXT("비어있음")));
		Txt_ItemName->SetColorAndOpacity(FLinearColor(0.6f, 0.6f, 0.6f));
	}
}

void USlotEquipItem::HandleEquipChanged(FGameplayTag InTag, const FMyItem& InItem)
{
	// 내 타입의 장착이 바뀌었을 때만 갱신
	if (InItem.ItemType != MyItemType)
	{
		return;
	}

	RefreshEquipped();
}
