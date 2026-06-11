// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupItemInfo.h"

#include "ETC/Define.h"
#include "ETC/Struct.h"
#include "Popup/PopupItemInfoVM.h"
#include "Slot/SlotItemInfo.h"

void UPopupItemInfo::OnDisable()
{
	Super::OnDisable();
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
	VALID_RETURN(VM, Slot_Selected, Slot_Equipped);

	Slot_Selected->SetData(VM->GetSelectedItemData());
	Slot_Selected->SetCompareData(VM->GetHPDiff(), VM->GetATKDiff(), VM->GetDEFDiff());

	// 같은 타입에 장착 중인 다른 아이템이 있을 때만 비교 대상 슬롯을 보여준다.
	if (VM->HasEquippedItem() && !VM->IsSelectedEquipped())
	{
		Slot_Equipped->SetData(VM->GetEquippedItemData());
		Slot_Equipped->HideCompare();
		Slot_Equipped->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Slot_Equipped->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPopupItemInfo::OnClickedEquip()
{
	VALID_RETURN(VM);

	// 이미 장착 중이면 할 일 없음
	if (VM->IsSelectedEquipped())
	{
		Hide();
		return;
	}

	VM->OnEquip();

	// 장착 슬롯 / 합산 능력치 갱신용 이벤트
	FMyItem EquippedItem = VM->GetSelectedItemData();
	EVENT_BROADCAST(TEXT("EquipChanged"), FMyItem, this, EquippedItem);

	Hide();
}
