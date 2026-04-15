// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
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
class WARLEGEND_API UPopupGachaVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
	void OnGachaOne();
	void OnGachaMulti(const int32 InItemCount);

	FOnToastRequested& GetOnToastRequested() { return OnToastRequested; }
	
private:
	void ShowToast(int32 InItemID);
	void ShowToastMulti(const TArray<int32>& InItemIDs);
	
private:
	FOnToastRequested OnToastRequested;
	
	UPROPERTY() 
	TObjectPtr<UPopupGachaLogVM> LogVM;
};
