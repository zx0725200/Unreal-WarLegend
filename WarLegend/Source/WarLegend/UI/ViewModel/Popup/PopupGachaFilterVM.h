// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "PopupGachaFilterVM.generated.h"

class USlotFilterVM;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilterSlotListChanged, const TArray<TObjectPtr<USlotFilterVM>>&);

/**
 *
 */
UCLASS()
class WARLEGEND_API UPopupGachaFilterVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void NotifyAll() override;

	const TArray<TObjectPtr<USlotFilterVM>>& GetSlotVMList() const { return SlotVMList; }

	FOnFilterSlotListChanged& GetOnSlotListChanged() { return OnSlotListChanged; }

private:
	UPROPERTY()
	TArray<TObjectPtr<USlotFilterVM>> SlotVMList;

	FOnFilterSlotListChanged OnSlotListChanged;
};

