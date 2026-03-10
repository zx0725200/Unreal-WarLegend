// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGacha.h"

#include "ViewModel/Popup/PopupGachaVM.h"

void UPopupGacha::Awake()
{
	Super::Awake();
}

void UPopupGacha::OnEnable()
{
	Super::OnEnable();
}

void UPopupGacha::OnDisable()
{
	Super::OnDisable();
	VM = nullptr;
}

void UPopupGacha::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	if (!VM) return;
	
	if (InChildName == TEXT("Btn_One"))
	{
		OnClickedOne();
	}
	else if (InChildName == TEXT("Btn_Ten"))
	{
		OnClickedTen();
	}
	else if (InChildName == TEXT("Btn_All"))
	{
		OnClickedAll();
	}
}

void UPopupGacha::SetViewModel(UPopupGachaVM* InVM)
{
	VM = InVM;
}

void UPopupGacha::OnClickedOne() const
{
	VM->OnClickOne.Broadcast();
}

void UPopupGacha::OnClickedTen() const
{
	VM->OnClickTen.Broadcast();
}

void UPopupGacha::OnClickedAll() const
{
	VM->OnClickAll.Broadcast();
}
