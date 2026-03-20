#pragma once

#include "Struct.generated.h"

struct FItemTableData;
enum class EItemType : uint8;
enum class EItemGrade : uint8;

USTRUCT(Blueprintable)
struct FMyItem
{
	GENERATED_BODY()

	void Init(const FItemTableData* InTableData, const FLinearColor& InGradeColor);
	
public:
	UPROPERTY()
	FName Name;
	
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

USTRUCT(Blueprintable)
struct FGachaLogData
{
	GENERATED_BODY()

public:
	FString ItemName;
	FLinearColor GradeColor;
	FString Time;
};