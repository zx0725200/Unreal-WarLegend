// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidgetBase.h"

void UScreenWidgetBase::Awake()
{
	Super::Awake();
}

void UScreenWidgetBase::OnEnable()
{
	Super::OnEnable();
}

void UScreenWidgetBase::OnDisable()
{
	Super::OnDisable();
}

FReply UScreenWidgetBase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
