// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGacha.h"

#include "ETC/Define.h"
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

	if (VM)
	{
		VM->ClearBinding();
	}
	VM = nullptr;
}

void UPopupGacha::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	VALID_RETURN(VM);

	if (InChildName == TEXT("Btn_One"))
	{
		VM->OnGachaOne();
	}
	else if (InChildName == TEXT("Btn_Ten"))
	{
		VM->OnGachaMulti(10);
	}
	else if (InChildName == TEXT("Btn_All"))
	{
		VM->OnGachaMulti(30);
	}
}

void UPopupGacha::BindViewModel()
{
	Super::BindViewModel();

	VM = NewObject<UPopupGachaVM>(this);
	VM->Init();
}
