// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "ETC/Enum.h"
#include "SlotEquipItemVM.generated.h"

struct FMyItem;
/**
 * 장착 슬롯(USlotEquipItem) 하나의 데이터/동작을 담당하는 ViewModel.
 */
UCLASS()
class WARLEGEND_API USlotEquipItemVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	void SetItemType(const EItemType InItemType);

	EItemType GetItemType() const { return ItemType; }

	// 이 타입에 장착된 아이템이 있는지
	bool HasEquipped() const;

	// 장착 아이템 표시 정보 (HasEquipped()가 true일 때만 유효)
	FString GetEquippedName() const;
	FLinearColor GetEquippedColor() const;

	// 클릭 시 장착 아이템 정보 팝업을 연다. (빈 슬롯이면 무시)
	void OnClickedSlot();

private:
	const FMyItem* FindEquipped() const;

private:
	EItemType ItemType = EItemType::None;
};
