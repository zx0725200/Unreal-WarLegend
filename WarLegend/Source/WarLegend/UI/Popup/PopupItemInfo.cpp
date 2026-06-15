// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupItemInfo.h"

#include "Components/TextBlock.h"
#include "ETC/Define.h"
#include "ETC/Struct.h"
#include "Popup/PopupItemInfoVM.h"
#include "Slot/SlotItemInfo.h"
#include "ViewModel/Slot/SlotItemInfoVM.h"

void UPopupItemInfo::OnDisable()
{
	Super::OnDisable();

	// 정보창이 닫히면 인벤토리에서 선택했던 슬롯도 선택 해제한다.
	// (어떤 실제 아이템과도 매칭되지 않는 UniqueID로 보내 모든 슬롯을 평상 상태로 되돌린다)
	FMyItem Deselect;
	Deselect.UniqueID = INDEX_NONE;
	EVENT_BROADCAST(TEXT("SelectItem"), FMyItem, this, Deselect);
}

void UPopupItemInfo::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);

	if (InChildName == TEXT("Btn_Equip"))
	{
		OnClickedEquip();
	}
}

void UPopupItemInfo::BindViewModel()
{
	Super::BindViewModel();

	// Outer를 지정해야 VM이 월드(매니저)를 찾을 수 있다.
	const auto PopupItemInfoVM = NewObject<UPopupItemInfoVM>(this);
	PopupItemInfoVM->Init();

	SetViewModel(PopupItemInfoVM);

	RefreshUI();
}

void UPopupItemInfo::SetViewModel(UPopupItemInfoVM* InVM)
{
	VM = InVM;
}

void UPopupItemInfo::RefreshUI() const
{
	RefreshSelectedSlot();
	RefreshEquippedSlot();
	RefreshEquipButton();
}

void UPopupItemInfo::RefreshSelectedSlot() const
{
	VALID_RETURN(VM, Slot_Selected);

	Slot_Selected->SetViewModel(VM->GetSelectedSlotVM());
}

void UPopupItemInfo::RefreshEquippedSlot() const
{
	VALID_RETURN(VM, Slot_Equipped);

	// 같은 타입에 장착 중인 다른 아이템이 있을 때만 비교 대상 슬롯을 보여준다.
	if (VM->HasEquippedItem() && !VM->IsSelectedEquipped())
	{
		Slot_Equipped->SetViewModel(VM->GetEquippedSlotVM());
		Slot_Equipped->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Slot_Equipped->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPopupItemInfo::RefreshEquipButton() const
{
	// 라벨 위젯이 없으면(BP에 미배치) 표시할 게 없다.
	if (!Txt_Equip)
	{
		return;
	}

	VALID_RETURN(VM);

	// 장착 중인 아이템이면 버튼을 "해제"로, 아니면 "장착"으로 표시한다.
	Txt_Equip->SetText(FText::FromString(VM->IsSelectedEquipped() ? TEXT("해제") : TEXT("장착")));
}

void UPopupItemInfo::OnClickedEquip()
{
	VALID_RETURN(VM);

	// 장착 중인 아이템이면 해제, 아니면 장착으로 동작한다.
	if (VM->IsSelectedEquipped())
	{
		VM->OnUnequip();
	}
	else
	{
		VM->OnEquip();
	}

	// 장착 슬롯 / 합산 능력치 / 인벤토리 목록 갱신용 이벤트
	FMyItem ChangedItem = VM->GetSelectedItemData();
	EVENT_BROADCAST(TEXT("EquipChanged"), FMyItem, this, ChangedItem);

	Hide();
}
