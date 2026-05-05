// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupItemInfo.h"

#include "Popup/PopupItemInfoVM.h"

void UPopupItemInfo::OnDisable()
{
	Super::OnDisable();
}

void UPopupItemInfo::BindViewModel()
{
	Super::BindViewModel();
	
	const auto PopupItemInfoVM = NewObject<UPopupItemInfoVM>();
	PopupItemInfoVM->Init();
	
	SetViewModel(PopupItemInfoVM);
}

void UPopupItemInfo::SetViewModel(UPopupItemInfoVM* InVM)
{
	VM = InVM;
}

