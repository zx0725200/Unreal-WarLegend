// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotGachaResultVM.h"

void USlotGachaResultVM::Init()
{
	Super::Init();
}

void USlotGachaResultVM::SetData(const FGachaLogData& InData, const int32 InRevealOrder)
{
	Data = InData;
	RevealOrder = InRevealOrder;
}
