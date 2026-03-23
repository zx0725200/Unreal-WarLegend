// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETC/Struct.h"
#include "UObject/Object.h"
#include "SlotInventoryVM.generated.h"

struct FItemTableData;
enum class EItemGrade : uint8;
enum class EItemType : uint8;
/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotInventoryVM : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(const FItemTableData* InTableData, const FLinearColor& InGradeColor);
	
	FMyItem ToSaveData() const;
	void FromSaveData(const FMyItem& InData);
	
public:
	UPROPERTY()
	int32 UniqueID = 0;
	
	UPROPERTY()
	int32 ID = 0;
	
	UPROPERTY()
	FString ItemName;
	
	UPROPERTY()
	FString ItemTypeName;
	
	UPROPERTY()
	FLinearColor ItemGradeColor;
	
	UPROPERTY()
	EItemType ItemType;
	
	UPROPERTY()
	EItemGrade ItemGrade;
	
	UPROPERTY()
	int32 HP = 0;
	
	UPROPERTY()
	int32 ATK = 0;
	
	UPROPERTY()
	int32 DEF = 0;
};
