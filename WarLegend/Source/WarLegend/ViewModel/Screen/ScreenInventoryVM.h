// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ScreenInventoryVM.generated.h"

enum class EItemType : uint8;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UScreenInventoryVM : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<EItemType> LeftItemTypes;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<EItemType> RightItemTypes;
};
