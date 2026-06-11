// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "ETC/Struct.h"
#include "PopupItemInfoVM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDataChanged, const FMyItem&, NewItem);
struct FMyItem;
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

	FMyItem& GetSelectedItemData() { return SelectedItemData; }
	const FMyItem& GetEquippedItemData() const { return EquippedItemData; }

	bool HasEquippedItem() const { return bHasEquippedItem; }
	bool IsSelectedEquipped() const { return bSelectedEquipped; }

	// 선택 아이템 - 장착 아이템 (장착이 없으면 0과 비교)
	int32 GetHPDiff() const;
	int32 GetATKDiff() const;
	int32 GetDEFDiff() const;

private:
	void RefreshEquippedData();

private:
	FMyItem SelectedItemData;
	FMyItem EquippedItemData;

	bool bHasEquippedItem = false;
	bool bSelectedEquipped = false;
};
