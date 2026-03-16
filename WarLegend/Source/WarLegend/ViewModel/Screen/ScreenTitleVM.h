// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenTitleVM.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnTitleConfirm);

UCLASS()
class WARLEGEND_API UScreenTitleVM : public UObject
{
	GENERATED_BODY()

public:
	void BroadCastConfirm();
	
	FOnTitleConfirm& GetConfirm() {return OnConfirmRequested;}
	
private:
	FOnTitleConfirm OnConfirmRequested;
};
