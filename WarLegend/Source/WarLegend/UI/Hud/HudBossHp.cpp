#include "HudBossHp.h"

#include "Components/ProgressBar.h"
#include "Hud/HudBossHpVM.h"

void UHudBossHp::OnDisable()
{
	VALID_RETURN(VM);
	
	UnbindVM();
	
	Super::OnDisable();
}

void UHudBossHp::BindViewModel()
{
	Super::BindViewModel();

	VM = NewObject<UHudBossHpVM>(this);
	VM->Init();
	
	BindVM();
}

void UHudBossHp::BindVM()
{
	VALID_RETURN(VM);
	BIND_VM(GetOnHpChanged, OnHpRatioChanged);
	
	OnHpRatioChanged(VM->GetHpRatio()); 
}

void UHudBossHp::UnbindVM()
{
	VALID_RETURN(VM);
	UNBIND_VM(GetOnHpChanged, OnHpRatioChanged);
	VM->ClearBinding();
}

void UHudBossHp::OnHpRatioChanged(const float InNewRatio)
{
	HpProgressBar->SetPercent(InNewRatio);
}