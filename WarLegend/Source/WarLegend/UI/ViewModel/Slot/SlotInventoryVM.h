// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETC/Struct.h"
#include "UObject/Object.h"
#include "SlotInventoryVM.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemInfoRequested, const FMyItem&);
/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotInventoryVM : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(const FMyItem& InData);
	void OpenPopupItemInfo();
	
	const FMyItem& GetMyItem() { return MyItem; }
	FOnItemInfoRequested& GetOnItemInfoRequested() { return OnItemInfoRequested; }

private:
	FMyItem MyItem;
	FOnItemInfoRequested OnItemInfoRequested;
};
