// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupGachaFilterVM.generated.h"

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
	UPROPERTY()
	TArray<TObjectPtr<USlotFilterVM>> SlotVMList;
	
	FOnFilterConfirm OnConfirm;
};
