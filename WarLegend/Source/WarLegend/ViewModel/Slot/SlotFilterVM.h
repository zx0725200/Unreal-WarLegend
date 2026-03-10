// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SlotFilterVM.generated.h"

enum class EItemGrade : uint8;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFilterChanged, EItemGrade, bool);

/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotFilterVM : public UObject
{
	GENERATED_BODY()
	
public:
	EItemGrade Grade;
	FString GradeName = TEXT("");
	bool bChecked = true;
	
	FOnFilterChanged OnFilterChanged;
};
