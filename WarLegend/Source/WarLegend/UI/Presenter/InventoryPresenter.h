// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryPresenter.generated.h"

struct FMyItem;
class UTableManager;
class UInventoryManager;
class UUIManagerImpl;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UInventoryPresenter : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(UUIManagerImpl* InUIMgr, UInventoryManager* InInvenMgr, UTableManager* InTableMgr);
	
	void OpenScreenInventory();
	void HandleOpenItemInfo(const FMyItem& InItem);
	
private:
	UPROPERTY()
	TObjectPtr<UUIManagerImpl> UIMgr;
	
	UPROPERTY()
	TObjectPtr<UInventoryManager> InvenMgr;
	
	UPROPERTY()
	TObjectPtr<UTableManager> TableMgr;
};
