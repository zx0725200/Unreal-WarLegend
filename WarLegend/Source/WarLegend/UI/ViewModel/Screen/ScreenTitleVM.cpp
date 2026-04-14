// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenTitleVM.h"

void UScreenTitleVM::BroadCastConfirm()
{
	OnConfirmRequested.Broadcast();
}
