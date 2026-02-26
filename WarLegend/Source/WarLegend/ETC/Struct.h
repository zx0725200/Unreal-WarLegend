#pragma once

#include "Struct.generated.h"

enum class EItemType : uint8;
enum class EItemGrade : uint8;

USTRUCT(Blueprintable)
struct FMyItem
{
	GENERATED_BODY()
	
	UPROPERTY()
	FName Name;
	
	UPROPERTY()
	int32 ID = 0;
};