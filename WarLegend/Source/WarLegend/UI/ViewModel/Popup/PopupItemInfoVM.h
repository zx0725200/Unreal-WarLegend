// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "ETC/Struct.h"
#include "PopupItemInfoVM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDataChanged, const FMyItem&, NewItem);
struct FMyItem;
class USlotItemInfoVM;

// 선택한 아이템과 같은 타입 장착 슬롯의 관계
enum class EEquipCompareState : uint8
{
	NoEquipped,		// 같은 타입에 장착된 게 없음
	OtherEquipped,	// 다른 아이템이 장착돼 있음 (비교 대상 존재)
	SelfEquipped	// 선택한 아이템이 바로 장착 중인 것
};

/**
 *
 */
UCLASS()
class WARLEGEND_API UPopupItemInfoVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	// 선택한 아이템을 장착한다. (같은 타입은 자동 교체)
	void OnEquip();

	// 선택한 (장착 중인) 아이템을 해제한다.
	void OnUnequip();

	FMyItem& GetSelectedItemData() { return SelectedItemData; }
	const FMyItem& GetEquippedItemData() const { return EquippedItemData; }

	bool HasEquippedItem() const { return EquipState != EEquipCompareState::NoEquipped; }
	bool IsSelectedEquipped() const { return EquipState == EEquipCompareState::SelfEquipped; }

	// 선택 슬롯 / 비교 대상 슬롯에 바인딩할 ViewModel
	USlotItemInfoVM* GetSelectedSlotVM() const { return SelectedSlotVM; }
	USlotItemInfoVM* GetEquippedSlotVM() const { return EquippedSlotVM; }

	// 선택 아이템 - 장착 아이템 (장착이 없으면 0과 비교)
	int32 GetHPDiff() const;
	int32 GetATKDiff() const;
	int32 GetDEFDiff() const;

private:
	void RefreshEquippedData();
	void BuildSlotVMs();

private:
	FMyItem SelectedItemData;
	FMyItem EquippedItemData;

	EEquipCompareState EquipState = EEquipCompareState::NoEquipped;

	UPROPERTY()
	TObjectPtr<USlotItemInfoVM> SelectedSlotVM;

	UPROPERTY()
	TObjectPtr<USlotItemInfoVM> EquippedSlotVM;
};
