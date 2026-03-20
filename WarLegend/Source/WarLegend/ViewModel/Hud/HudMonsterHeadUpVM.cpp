// Fill out your copyright notice in the Description page of Project Settings.


#include "HudMonsterHeadUpVM.h"

#include "Character/Monster.h"

void UHudMonsterHeadUpVM::Init(AMonster* InMonster)
{
	LapCount = 0;
	if (!InMonster) return;
 
	InMonster->OnLapCountChanged.AddUObject(this, &UHudMonsterHeadUpVM::HandleLapCountChanged);
}

void UHudMonsterHeadUpVM::HandleLapCountChanged(AMonster* InMonster, const int32 InNewLapCount)
{
	LapCount = InNewLapCount;
	OnLapCountUpdated.Broadcast(LapCount);
}
