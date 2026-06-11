#include "ScreenInventory.h"

#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "Components/VerticalBox.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "Slot/SlotEquipItem.h"
#include "ViewModel/Screen/ScreenInventoryVM.h"
#include "ViewModel/Slot/SlotInventoryVM.h"

void UScreenInventory::Awake()
{
	Super::Awake();
}

void UScreenInventory::OnEnable()
{
	Super::OnEnable();
}

void UScreenInventory::OnDisable()
{
	Super::OnDisable();
}

void UScreenInventory::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Reset"))
	{
		OnClickedReset();
	}
}

FReply UScreenInventory::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UScreenInventory::SetViewModel(UScreenInventoryVM* InData)
{
	VM = InData;
}

void UScreenInventory::BindViewModel()
{
	Super::BindViewModel();
	
	auto* InventoryVM = NewObject<UScreenInventoryVM>(this);
	InventoryVM->Init();
	
	SetViewModel(InventoryVM);

	InitEquipSlots();
	InitInventorySlots();
	RefreshTotalStats();

	// 팝업에서 장착이 바뀌면 합산 능력치 갱신
	EVENT_LISTEN(TEXT("EquipChanged"), FMyItem, this, &ThisClass::HandleEquipChanged);
}

void UScreenInventory::InitEquipSlots()
{
	VALID_RETURN(VM);
	CreateEquipSlots(Vertical_Equip, VM->GetLeftItemTypes());
	CreateEquipSlots(Vertical_Boss, VM->GetRightItemTypes());
}

void UScreenInventory::InitInventorySlots()
{
	VALID_RETURN(VM);
	TileView_Inventory->ClearListItems();
	for (const auto& HavingItem : VM->GetItems())
	{
		TileView_Inventory->AddItem(HavingItem);
	}
}

void UScreenInventory::CreateEquipSlots(UVerticalBox* InParent, const TMap<EItemType, FString>& InItemData) const
{
	InParent->ClearChildren();
	for (const auto& EquipItem : InItemData)
	{
		USlotEquipItem* SlotEquipItem = CreateWidget<USlotEquipItem>(GetWorld(), EquipSlotClass);
		VALID_RETURN(SlotEquipItem);
		
		SlotEquipItem->SetData(EquipItem.Key, EquipItem.Value);
		
		InParent->AddChild(SlotEquipItem);
	}
}

void UScreenInventory::RefreshTotalStats() const
{
	VALID_RETURN(VM);

	const FEquipStatTotal Total = VM->GetEquippedStatTotal();

	Txt_TotalHP->SetText(FText::FromString(FString::Printf(TEXT("HP %d"), Total.HP)));
	Txt_TotalATK->SetText(FText::FromString(FString::Printf(TEXT("ATK %d"), Total.ATK)));
	Txt_TotalDEF->SetText(FText::FromString(FString::Printf(TEXT("DEF %d"), Total.DEF)));
}

void UScreenInventory::OnClickedReset()
{
	VALID_RETURN(VM);

	TileView_Inventory->ClearListItems();
	VM->OnReset();

	// 장착 슬롯과 합산 능력치도 초기화 상태로 갱신
	InitEquipSlots();
	RefreshTotalStats();
}

void UScreenInventory::HandleEquipChanged(FGameplayTag InTag, const FMyItem& InItem)
{
	RefreshTotalStats();
}
