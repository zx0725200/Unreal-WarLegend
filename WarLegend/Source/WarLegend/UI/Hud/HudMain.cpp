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
	
	VM = NewObject<UHudMainVM>(this);
	VM->Init();
}
