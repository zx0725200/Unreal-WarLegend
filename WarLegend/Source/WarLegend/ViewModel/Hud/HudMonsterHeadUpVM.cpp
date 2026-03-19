// Fill out your copyright notice in the Description page of Project Settings.


#include "HudMonsterHeadUpVM.h"

void UHudMonsterHeadUpVM::SetLapCount(const int32 InCount)
{
	LapCount = InCount;
	OnLapCountUpdated.Broadcast(LapCount);
}
