// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupDungeonMenuVM.h"

void UPopupDungeonMenuVM::SetName(const FString& InName)
{
	Name = InName;
	OnNameChanged.Broadcast(Name);
}

void UPopupDungeonMenuVM::SetLevel(const int32 InMin, const int32 InMax)
{
	MinLevel = InMin;
	MaxLevel = InMax;
	OnLevelChanged.Broadcast(MinLevel, MaxLevel);
}

void UPopupDungeonMenuVM::SetID(const int32 InID)
{
	ID = InID;
}

void UPopupDungeonMenuVM::BroadCastConfirm()
{
	OnConfirmRequested.Broadcast(ID);
}
