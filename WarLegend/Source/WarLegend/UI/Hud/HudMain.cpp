#include "HudMain.h"
#include "Hud/HudMainVM.h"

void UHudMain::Awake()
{
	Super::Awake();
}

void UHudMain::OnEnable()
{
	Super::OnEnable();
}

void UHudMain::OnDisable()
{
	Super::OnDisable();
}

void UHudMain::BindViewModel()
{
	Super::BindViewModel();
	
	auto* HudMainVM = NewObject<UHudMainVM>(this);
	HudMainVM->Init();
}
