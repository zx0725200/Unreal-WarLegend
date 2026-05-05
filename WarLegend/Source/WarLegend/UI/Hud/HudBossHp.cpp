// Fill out your copyright notice in the Description page of Project Settings.


#include "HudBossHp.h"

#include "Components/ProgressBar.h"
#include "Hud/HudBossHpVM.h"

void UHudBossHp::SetViewModel(UHudBossHpVM* InViewModel)
{
	UnbindVM();
	
	VM = InViewModel;
	
	BindVM();
}

void UHudBossHp::OnHpRatioChanged(const float InNewRatio)
{
	HpProgressBar->SetPercent(InNewRatio);
}

void UHudBossHp::OnDisable()
{
	VALID_RETURN(VM);
	
	VM->GetOnHpChanged().RemoveDynamic(this, &UHudBossHp::OnHpRatioChanged);
	VM->ClearBinding();
	
	Super::OnDisable();
}

void UHudBossHp::BindViewModel()
{
	Super::BindViewModel();

	auto* HudBossHpVM = NewObject<UHudBossHpVM>(this);
	HudBossHpVM->Init();
	SetViewModel(HudBossHpVM);
}

void UHudBossHp::BindVM()
{
	VALID_RETURN(VM);
	
	VM->GetOnHpChanged().AddDynamic(this, &UHudBossHp::OnHpRatioChanged);
	OnHpRatioChanged(VM->GetHpRatio()); 
}

void UHudBossHp::UnbindVM()
{
	VALID_RETURN(VM);
	
	VM->GetOnHpChanged().RemoveDynamic(this, &UHudBossHp::OnHpRatioChanged);
}
