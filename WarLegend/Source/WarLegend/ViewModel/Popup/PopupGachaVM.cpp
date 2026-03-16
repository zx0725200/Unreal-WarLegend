// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaVM.h"

void UPopupGachaVM::BroadCastOne()
{
	OnClickOne.Broadcast();
}

void UPopupGachaVM::BroadCastTen()
{
	OnClickTen.Broadcast();
}

void UPopupGachaVM::BroadCastAll()
{
	OnClickAll.Broadcast();
}
