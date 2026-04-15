// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
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
class WARLEGEND_API UPopupGachaFilterVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	const TArray<TObjectPtr<USlotFilterVM>>& GetSlotVMList() const { return SlotVMList; }

private:
	UPROPERTY()
	TArray<TObjectPtr<USlotFilterVM>> SlotVMList;
};
