// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GachaPresenter.generated.h"

class UInventoryManager;
class UGachaManager;
class UUIManagerImpl;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UGachaPresenter : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(UUIManagerImpl* InUIMgr, UGachaManager* InGachaMgr, UInventoryManager* InInvenMgr);

	void OpenPopupGacha();

private:
	void HandleClickOne();
	void HandleClickTen();
	void HandleClickAll();

private:
	UPROPERTY()
	TObjectPtr<UUIManagerImpl> UIMgr;

	UPROPERTY()
	TObjectPtr<UGachaManager> GachaMgr;

	UPROPERTY()
	TObjectPtr<UInventoryManager> InvenMgr;
};
