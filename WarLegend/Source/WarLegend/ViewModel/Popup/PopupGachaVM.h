// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PopupGachaVM.generated.h"

struct FGachaLogData;
class UPopupGachaLogVM;
class UUIManagerImpl;
class UTableManager;
class UInventoryManager;
class UGachaManager;
DECLARE_MULTICAST_DELEGATE(FOnToastRequested);

/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupGachaVM : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(UGachaManager* InGachaMgr, UInventoryManager* InInvenMgr, UTableManager* InTableMgr, UUIManagerImpl* InUIMgr, UPopupGachaLogVM* InLogVM);
	
	void BroadCastOne();
	void BroadCastTen();
	void BroadCastAll();

	FOnToastRequested& GetOnToastRequested() { return OnToastRequested; }
	
private:
	void ShowToast(int32 InItemID);
	void ShowToastMulti(const TArray<int32>& InItemIDs);
	
private:
	FOnToastRequested OnToastRequested;
	
	UPROPERTY() 
	TObjectPtr<UGachaManager> GachaMgr;
	
	UPROPERTY() 
	TObjectPtr<UInventoryManager> InvenMgr;
	
	UPROPERTY() 
	TObjectPtr<UTableManager> TableMgr;
	
	UPROPERTY() 
	TObjectPtr<UUIManagerImpl> UIMgr;
	
	UPROPERTY() 
	TObjectPtr<UPopupGachaLogVM> LogVM;
};
