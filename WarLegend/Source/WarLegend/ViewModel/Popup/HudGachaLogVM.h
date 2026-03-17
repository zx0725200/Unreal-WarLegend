// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETC/Struct.h"
#include "UObject/Object.h"
#include "HudGachaLogVM.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnLogUpdated);
DECLARE_MULTICAST_DELEGATE(FOnLogCleared);

UCLASS()
class WARLEGEND_API UHudGachaLogVM : public UObject
{
	GENERATED_BODY()
	
public:
	void AddLog(const FGachaLogData& InData);
	void ClearAll();
	
	const TArray<FGachaLogData>& GetLogList() const { return LogList; }
	FOnLogUpdated& GetOnLogUpdated() { return OnLogUpdated; }
	FOnLogCleared& GetOnLogCleared() { return OnLogCleared; }
	
private:
	TArray<FGachaLogData> LogList;
	
	FOnLogUpdated OnLogUpdated;
	FOnLogCleared OnLogCleared;
};
