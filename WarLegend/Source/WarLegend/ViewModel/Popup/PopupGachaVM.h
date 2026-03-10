// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PopupGachaVM.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGachaRequested);

/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupGachaVM : public UObject
{
	GENERATED_BODY()
	
public:
	FOnGachaRequested OnClickOne;
	FOnGachaRequested OnClickTen;
	FOnGachaRequested OnClickAll;
};
