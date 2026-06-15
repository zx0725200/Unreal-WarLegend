// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "ETC/Struct.h"
#include "ETC/Enum.h"
#include "ScreenInventoryVM.generated.h"

struct FMyItem;
class USlotInventoryVM;
enum class EItemType : uint8;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UScreenInventoryVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	void OnReset();

	// 장착 상태가 바뀐 뒤 인벤토리 목록(장착템 제외)을 다시 만든다.
	void RefreshItems();

	// 설정된 등급 필터에 해당하는 아이템을 모두 버리고 목록을 갱신한다.
	void DiscardByFilter();

	// 버리기 등급 설정 팝업을 연다.
	void OpenDiscardSetting();

	// 등급/스탯 기준 정렬 방향을 토글한다.
	void ToggleSort();
	ESortOrder GetSortOrder() const { return SortOrder; }

	// 장착 중인 아이템들의 능력치 합산
	FEquipStatTotal GetEquippedStatTotal() const;

	const TArray<TObjectPtr<USlotInventoryVM>>& GetItems() { return ItemList; }
	const TMap<EItemType, FString>& GetLeftItemTypes() { return LeftItemTypes; }
	const TMap<EItemType, FString>& GetRightItemTypes() { return RightItemTypes; }

private:
	void AddItemList();
	void SortItemList();

private:
	UPROPERTY()
	TArray<TObjectPtr<USlotInventoryVM>> ItemList;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> LeftItemTypes;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> RightItemTypes;

	ESortOrder SortOrder = ESortOrder::Descending;
};
