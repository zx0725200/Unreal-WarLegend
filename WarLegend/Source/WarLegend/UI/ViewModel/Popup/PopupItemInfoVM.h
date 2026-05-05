// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "ETC/Struct.h"
#include "PopupItemInfoVM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDataChanged, const FMyItem&, NewItem);
struct FMyItem;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupItemInfoVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
	FMyItem& GetSelectedItemData() { return SelectedItemData; }

private:
	FMyItem SelectedItemData;
};
