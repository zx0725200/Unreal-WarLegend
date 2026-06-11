// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "ETC/Struct.h"
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

	// 장착 중인 아이템들의 능력치 합산
	FEquipStatTotal GetEquippedStatTotal() const;

	const TArray<TObjectPtr<USlotInventoryVM>>& GetItems() { return ItemList; }
	const TMap<EItemType, FString>& GetLeftItemTypes() { return LeftItemTypes; }
	const TMap<EItemType, FString>& GetRightItemTypes() { return RightItemTypes; }

private:
	void AddItemList();
	
private:
	UPROPERTY()
	TArray<TObjectPtr<USlotInventoryVM>> ItemList;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> LeftItemTypes;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> RightItemTypes;
};
