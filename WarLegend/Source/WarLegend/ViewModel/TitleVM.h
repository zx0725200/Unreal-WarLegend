// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TitleVM.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UTitleVM : public UObject
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
