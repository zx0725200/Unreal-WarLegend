// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupGachaFilterVM.generated.h"

enum class EItemGrade : uint8;
class USaveGameDataManager;
class UGachaManager;
class UUIManagerImpl;
class UWLSaveGame;
class USlotFilterVM;

DECLARE_MULTICAST_DELEGATE(FOnFilterConfirm);
/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupGachaFilterVM : public UPopupWidgetBase
{
	GENERATED_BODY()

public:
	void Init(const UUIManagerImpl* InUIMgr, USaveGameDataManager* InSaveGameMgr, UGachaManager* InGachaMgr);
	void HandleFilterChanged(const EItemGrade InGrade, const bool bChecked);
	
	const TArray<TObjectPtr<USlotFilterVM>>& GetSlotVMList() const { return SlotVMList; }

private:
	UPROPERTY()
	TArray<TObjectPtr<USlotFilterVM>> SlotVMList;
	
	UPROPERTY() 
	TObjectPtr<USaveGameDataManager> SaveGameMgr;
	
	UPROPERTY() 
	TObjectPtr<UGachaManager> GachaMgr;
};
