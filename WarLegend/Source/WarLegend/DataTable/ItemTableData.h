// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemTableData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemTableData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ID = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HP = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ATK = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DEF = 0;
};
