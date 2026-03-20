// Fill out your copyright notice in the Description page of Project Settings.


#include "HudMonsterHeadUp.h"

#include "Components/TextBlock.h"
#include "ViewModel/Hud/HudMonsterHeadUpVM.h"

void UHudMonsterHeadUp::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!Txt_Count)
	{
		return;
	}
	
	Txt_Count->SetText(FText::FromString(TEXT("0")));
}

void UHudMonsterHeadUp::NativeDestruct()
{
	VM = nullptr;
	Super::NativeDestruct();
}

void UHudMonsterHeadUp::SetViewModel(UHudMonsterHeadUpVM* InVM)
{
	VM = InVM;
	if (!VM)
	{
		return;
	}
	
	VM->GetOnLapCountUpdated().AddUObject(this, &UHudMonsterHeadUp::OnLapCountUpdated);
	
	OnLapCountUpdated(VM->GetLapCount());
}

void UHudMonsterHeadUp::OnLapCountUpdated(const int32 NewCount)
{
	if (!Txt_Count)
	{
		return;
	}
	
	Txt_Count->SetText(FText::AsNumber(NewCount));
}
