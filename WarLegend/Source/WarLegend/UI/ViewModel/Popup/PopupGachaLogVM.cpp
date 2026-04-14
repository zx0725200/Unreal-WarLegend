// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaLogVM.h"

void UPopupGachaLogVM::AddLog(const FGachaLogData& InData)
{
	LogList.Add(InData);
}

void UPopupGachaLogVM::ClearAll()
{
	LogList.Empty();
	OnLogCleared.Broadcast();
}
