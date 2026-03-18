#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DungeonTableData.generated.h"

UENUM(BlueprintType)
enum class EDungeonType : uint8
{
	Easy		UMETA(DisplayName="Easy"),
	Normal		UMETA(DisplayName="Normal"),
	Hard		UMETA(DisplayName="Hard"),
};

USTRUCT(BlueprintType)
struct FDungeonTableData : public  FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DungeonID = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DungeonName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDungeonType DungeonType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TierIndex = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MinLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxLevel = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EnemyHpScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EnemyAtkScale = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector SpawnLocation = FVector::ZeroVector;
};
