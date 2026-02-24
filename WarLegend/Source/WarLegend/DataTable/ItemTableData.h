// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemTableData.generated.h"

/**
 * 
 */

enum class EItemType : uint8;
enum class EItemGrade : uint8;

USTRUCT(BlueprintType)
struct FItemTableData : public FTableRowBase
{
	GENERATED_BODY()
	
	FItemTableData();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ID = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemTypeName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor ItemGradeColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemGrade ItemGrade;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HP = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ATK = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DEF = 0;
};
