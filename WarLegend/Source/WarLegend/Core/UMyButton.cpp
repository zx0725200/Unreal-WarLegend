// Fill out your copyright notice in the Description page of Project Settings.


#include "UMyButton.h"

UUMyButton::UUMyButton(const FObjectInitializer& ObjectInitializer)
{
	InitIsFocusable(false);
}

void UUMyButton::RegActionBase()
{
	OnClicked.AddDynamic(this, &UUMyButton::OnClickBase);
}

void UUMyButton::OnClickBase()
{
	if (OnClickWithNamed.IsBound())
	{
		OnClickWithNamed.Broadcast(GetFName());
	}
}
