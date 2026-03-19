// Fill out your copyright notice in the Description page of Project Settings.


#include "HudMonsterHeadUp.h"

#include "ViewModel/Hud/HudMonsterHeadUpVM.h"

void UHudMonsterHeadUp::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Txt_Count)
	{
		Txt_Count->SetText(FText::FromString(TEXT("0")));
	}
}

void UHudMonsterHeadUp::NativeDestruct()
{
	Super::NativeDestruct();
}

void UHudMonsterHeadUp::SetViewModel(UHudMonsterHeadUpVM* InVM)
{
	VM = InVM;
	if (!VM) return;
 
	// VM 델리게이트 구독
	VM->GetOnLapCountUpdated().AddUObject(this, &UHudMonsterHeadUp::OnLapCountUpdated);
 
	// 초기값 반영
	OnLapCountUpdated(VM->GetLapCount());
}

void UHudMonsterHeadUp::OnLapCountUpdated(const int32 NewCount)
{
	if (Txt_Count)
	{
		Txt_Count->SetText(FText::AsNumber(NewCount));
	}
}
