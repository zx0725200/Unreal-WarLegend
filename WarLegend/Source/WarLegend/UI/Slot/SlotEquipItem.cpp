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
	VALID_RETURN(VM);
	
	Super::OnClickEvent(InChildName);

	if (InChildName == TEXT("Btn_Slot"))
	{
		VM->OnClickedSlot();
	}
}

void USlotEquipItem::SetData(const EItemType InItemType, const FString& InItemName)
{
	VM = NewObject<USlotEquipItemVM>(this);
	VM->SetItemType(InItemType);

	Txt_Name->SetText(FText::FromString(InItemName));

	RefreshEquipItemName();

	EVENT_LISTEN(TEXT("EquipChanged"), FMyItem, this, &ThisClass::HandleEquipChanged);
}

void USlotEquipItem::RefreshEquipItemName() const
{
	VALID_RETURN(VM, Txt_ItemName);

	const bool bEquipped = VM->HasEquipped();
	const FString EquipItemName = VM->GetEquippedName();
	const FString EmptyItemName = TEXT("비어있음");
	const FLinearColor EquipColor = VM->GetEquippedColor();
	const FLinearColor BaseColor = FLinearColor(0.6f, 0.6f, 0.6f);
	
	Txt_ItemName->SetText(FText::FromString(bEquipped ? EquipItemName : EmptyItemName));
	Txt_ItemName->SetColorAndOpacity(bEquipped ? EquipColor : BaseColor);
}

void USlotEquipItem::HandleEquipChanged(FGameplayTag InTag, const FMyItem& InItem)
{
	VALID_RETURN(VM);

	// 내 타입의 장착이 바뀌었을 때만 갱신
	if (InItem.ItemType != VM->GetItemType())
	{
		return;
	}

	RefreshEquipItemName();
}
