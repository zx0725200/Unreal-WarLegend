// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupCharacterSelect.h"

void UPopupCharacterSelect::OnEnable()
{
	Super::OnEnable();
}

void UPopupCharacterSelect::OnDisable()
{
	Super::OnDisable();
}

void UPopupCharacterSelect::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Confirm"))
	{
		Hide();
	}
}
