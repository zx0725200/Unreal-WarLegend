// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenTitleVM.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UScreenTitleVM : public UObject
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE(FOnConfirmRequested);
	FOnConfirmRequested OnConfirmRequested;

	UFUNCTION()
	void Confirm() const
	{
		OnConfirmRequested.Broadcast();
	}
};
