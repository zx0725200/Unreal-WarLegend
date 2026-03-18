// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GachaPresenter.generated.h"

struct FGachaLogData;
class UPopupGachaLogVM;
class UTableManager;
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
	void Init(UUIManagerImpl* InUIMgr, UGachaManager* InGachaMgr, UInventoryManager* InInvenMgr, USaveGameDataManager* InSaveGameMgr, UTableManager* InTableMgr);

	void OpenPopupGacha();
	void OpenPopupGachaFilter();
	void OpenPopupGachaLog();
	
private:
	void HandleShowToast();

private:
	UPROPERTY()
	TObjectPtr<UUIManagerImpl> UIMgr;

	UPROPERTY()
	TObjectPtr<UGachaManager> GachaMgr;

	UPROPERTY()
	TObjectPtr<UInventoryManager> InvenMgr;
	
	UPROPERTY()
	TObjectPtr<USaveGameDataManager> SaveGameMgr;
	
	UPROPERTY()
	TObjectPtr<UTableManager> TableMgr;
	
	UPROPERTY()
	TObjectPtr<UPopupGachaLogVM> GachaLogVM;
};
