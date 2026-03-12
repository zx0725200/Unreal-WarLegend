// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GachaPresenter.generated.h"

enum class EItemGrade : uint8;
class USaveGameDataManager;
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
	void Init(UUIManagerImpl* InUIMgr, UGachaManager* InGachaMgr, UInventoryManager* InInvenMgr, USaveGameDataManager* InSaveGameMgr);

	void OpenPopupGacha();
	void OpenPopupGachaFilter();

private:
	void ApplyFilter();
	
	void HandleClickOne();
	void HandleClickTen();
	void HandleClickAll();
	
	void HandleFilterChanged(EItemGrade Grade, bool bChecked);

private:
	UPROPERTY()
	TObjectPtr<UUIManagerImpl> UIMgr;

	UPROPERTY()
	TObjectPtr<UGachaManager> GachaMgr;

	UPROPERTY()
	TObjectPtr<UInventoryManager> InvenMgr;
	
	UPROPERTY()
	TObjectPtr<USaveGameDataManager> SaveGameMgr;
};
