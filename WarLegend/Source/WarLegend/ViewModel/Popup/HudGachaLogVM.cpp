// Fill out your copyright notice in the Description page of Project Settings.


#include "HudGachaLogVM.h"

void UHudGachaLogVM::AddLog(const FGachaLogData& InData)
{
	LogList.Add(InData);
	OnLogUpdated.Broadcast();
}

void UHudGachaLogVM::ClearAll()
{
	LogList.Empty();
	OnLogCleared.Broadcast();
}
