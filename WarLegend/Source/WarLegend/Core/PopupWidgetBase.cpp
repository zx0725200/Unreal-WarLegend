// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PopupWidgetBase.h"

void UPopupWidgetBase::Awake()
{
	Super::Awake();
}

void UPopupWidgetBase::OnEnable()
{
	Super::OnEnable();
}

void UPopupWidgetBase::OnDisable()
{
	Super::OnDisable();
}

void UPopupWidgetBase::OnDestroy()
{
	Super::OnDestroy();
}

void UPopupWidgetBase::Update(const float InDeltaTime)
{
	Super::Update(InDeltaTime);
}

void UPopupWidgetBase::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Exit") || InChildName == TEXT("Btn_Cancel"))
	{
		Hide();
	}
}
