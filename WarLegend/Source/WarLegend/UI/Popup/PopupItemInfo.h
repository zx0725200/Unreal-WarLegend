// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupItemInfo.generated.h"

class UPopupItemInfoVM;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupItemInfo : public UPopupWidgetBase
{
	GENERATED_BODY()

public:
	virtual void OnDisable() override;
	virtual void BindViewModel() override;
	
private:
	void SetViewModel(UPopupItemInfoVM* InVM);

private:
	UPROPERTY()
	TObjectPtr<UPopupItemInfoVM> VM;
};
