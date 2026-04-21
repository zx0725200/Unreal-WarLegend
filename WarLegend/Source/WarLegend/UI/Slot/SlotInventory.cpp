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
	VALID_RETURN(VM);
	
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
	const auto MyItem = VM->GetMyItem();
	
	const auto ItemColor = MyItem.ItemGradeColor;
	const FText ItemName = FText::FromString(MyItem.ItemName);
	const FText ItemTypeName = FText::FromString(MyItem.ItemTypeName);
	
	Txt_Grade->SetText(ItemTypeName);
	Txt_Grade->SetColorAndOpacity(ItemColor);
	
	Txt_Name->SetText(ItemName);
	Txt_Name->SetColorAndOpacity(ItemColor);
}

void USlotInventory::OnClickedSlot()
{
	VALID_RETURN(VM);
	auto MyItem = VM->GetMyItem();
	MyItem.EventName = TEXT("SelectItem");
	
	EVENT_BROADCAST(MyItem.EventName, FMyItem, this, MyItem);
}

void USlotInventory::SetSelectedState()
{
	VALID_RETURN(VM);
	
	Img_Select->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Img_NotSelect->SetVisibility(ESlateVisibility::Collapsed);
	
	VM->OnOpenItemInfo();
}

void USlotInventory::SetNormalState()
{
	Img_Select->SetVisibility(ESlateVisibility::Collapsed);
	Img_NotSelect->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void USlotInventory::HandleClickedSlot(FGameplayTag InTag, const FMyItem& InItem)
{
	const auto MyItem = VM->GetMyItem();
	
	if (InItem.UniqueID == MyItem.UniqueID)
	{
		SetSelectedState();
	}
	else
	{
		SetNormalState();
	}
}
