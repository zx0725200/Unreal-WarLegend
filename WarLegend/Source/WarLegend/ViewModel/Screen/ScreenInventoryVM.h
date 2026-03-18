// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataManager/InventoryManager.h"
#include "UObject/Object.h"
#include "ScreenInventoryVM.generated.h"

class UTableManager;
class UInventoryManager;
class USlotInventoryVM;
enum class EItemType : uint8;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UScreenInventoryVM : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(UInventoryManager* InMgr, UTableManager* TableMgr);
	
	const TArray<TObjectPtr<USlotInventoryVM>>& GetItems() const;
	const TMap<EItemType, FString>& GetLeftItemTypes() const;
	const TMap<EItemType, FString>& GetLightItemTypes() const;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> LeftItemTypes;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> RightItemTypes;
	
	UPROPERTY()
	TObjectPtr<UInventoryManager> InvenMgr;
};
