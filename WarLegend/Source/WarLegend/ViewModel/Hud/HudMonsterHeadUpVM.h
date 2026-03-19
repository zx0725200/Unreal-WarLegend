// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HudMonsterHeadUpVM.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLapCountUpdated, int32);

/**
 * 
 */
UCLASS()
class WARLEGEND_API UHudMonsterHeadUpVM : public UObject
{
	GENERATED_BODY()
	
public:
	void SetLapCount(int32 InCount);
	
	int32 GetLapCount() const { return LapCount; }
	FOnLapCountUpdated& GetOnLapCountUpdated() { return OnLapCountUpdated; }
 
private:
	int32 LapCount = 0;
	FOnLapCountUpdated OnLapCountUpdated;
};
