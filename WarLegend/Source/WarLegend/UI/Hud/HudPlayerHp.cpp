#include "HudPlayerHp.h"

#include "Components/ProgressBar.h"
#include "Hud/HudPlayerHpVM.h"

void UHudPlayerHp::OnDisable()
{
	VALID_RETURN(VM);

	UnbindVM();

	Super::OnDisable();
}

void UHudPlayerHp::BindViewModel()
{
	Super::BindViewModel();

	VM = NewObject<UHudPlayerHpVM>(this);
	VM->Init();

	BindVM();
}

void UHudPlayerHp::BindVM()
{
	VALID_RETURN(VM);
	BIND_VM(GetOnHpChanged, OnHpRatioChanged);

	OnHpRatioChanged(VM->GetHpRatio());
}

void UHudPlayerHp::UnbindVM()
{
	VALID_RETURN(VM);
	UNBIND_VM(GetOnHpChanged, OnHpRatioChanged);
	VM->ClearBinding();
}

void UHudPlayerHp::OnHpRatioChanged(const float InNewRatio)
{
	HpProgressBar->SetPercent(InNewRatio);
}
