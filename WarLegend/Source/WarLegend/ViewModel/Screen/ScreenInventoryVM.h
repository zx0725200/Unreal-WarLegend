// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ViewModel/Slot/SlotInventoryVM.h"
#include "ScreenInventoryVM.generated.h"

class UUIManagerImpl;
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
	void Init(UInventoryManager* InMgr, UTableManager* InTableMgr);
	void RefreshItems();
	
	void HandleReset();
	void HandleOpenItemInfo(const FMyItem& InItem);
	
	const TArray<TObjectPtr<USlotInventoryVM>>& GetItems() const;
	const TMap<EItemType, FString>& GetLeftItemTypes() const;
	const TMap<EItemType, FString>& GetLightItemTypes() const;
	FOnItemInfoRequested& GetOnItemInfoRequested() { return OnItemInfoRequested; }
	
private:
	UPROPERTY()
	TArray<TObjectPtr<USlotInventoryVM>> Items;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> LeftItemTypes;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, FString> RightItemTypes;
	
	UPROPERTY()
	TObjectPtr<UInventoryManager> InvenMgr;
	
	FOnItemInfoRequested OnItemInfoRequested;
};
