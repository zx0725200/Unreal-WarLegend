// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
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
	
	const TArray<TObjectPtr<USlotInventoryVM>>& GetItems() { return Items; }
	const TMap<EItemType, FString>& GetLeftItemTypes() { return LeftItemTypes; }
	const TMap<EItemType, FString>& GetRightItemTypes() { return RightItemTypes; }

private:
	void RefreshItems();
	
private:
	UPROPERTY()
	TArray<TObjectPtr<USlotInventoryVM>> Items;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> LeftItemTypes;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> RightItemTypes;
};
