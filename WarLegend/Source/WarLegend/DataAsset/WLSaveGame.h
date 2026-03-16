// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WLSaveGame.generated.h"

struct FMyItem;
enum class EItemGrade : uint8;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UWLSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TMap<EItemGrade, bool> GachaFilter;
	
	UPROPERTY()
	TMap<int32, FMyItem> InvenItemData;
};
