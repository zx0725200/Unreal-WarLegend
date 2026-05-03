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

void UHudBossHp::OnHpRatioChanged(float NewRatio)
{
	HpProgressBar->SetPercent(NewRatio);
}

void UHudBossHp::NativeDestruct()
{
	if (VM)
	{
		VM->OnHpRatioChanged.RemoveDynamic(this, &UHudBossHp::OnHpRatioChanged);
		VM->ClearBinding();
	}

	Super::NativeDestruct();
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
	if (VM)
	{
		VM->OnHpRatioChanged.AddDynamic(this, &UHudBossHp::OnHpRatioChanged);
		OnHpRatioChanged(VM->GetHpRatio()); // 초기값 즉시 반영
	}
}

void UHudBossHp::UnbindVM()
{
	if (VM)
	{
		VM->OnHpRatioChanged.RemoveDynamic(this, &UHudBossHp::OnHpRatioChanged);
	}
}
