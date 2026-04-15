// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "ETC/Struct.h"
#include "SlotInventoryVM.generated.h"

struct FMyItem;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemInfoRequested, const FMyItem&);
/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotInventoryVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	void Init(const FMyItem& InData);
	void OnOpenItemInfo();
	
	const FMyItem& GetMyItem() { return MyItem; }

private:
	FMyItem MyItem;
};
