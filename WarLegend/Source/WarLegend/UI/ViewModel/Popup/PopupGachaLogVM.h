// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "ETC/Struct.h"
#include "PopupGachaLogVM.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnLogUpdated);
DECLARE_MULTICAST_DELEGATE(FOnLogCleared);

UCLASS()
class WARLEGEND_API UPopupGachaLogVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	void AddLog(const FGachaLogData& InData);
	void ClearAll();
	
	const TArray<FGachaLogData>& GetLogList() const { return LogList; }
	FOnLogCleared& GetOnLogCleared() { return OnLogCleared; }
	
private:
	TArray<FGachaLogData> LogList;
	
	FOnLogCleared OnLogCleared;
};
