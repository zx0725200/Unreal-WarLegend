#include "HudLeftMenu.h"
#include "Hud/HudLeftVM.h"

void UHudLeftMenu::OnDisable()
{
	Super::OnDisable();
	VM = nullptr;
}

void UHudLeftMenu::OnClickEvent(const FName& InChildName)
{
	VALID_RETURN(VM);
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Inven"))
	{
		VM->OnClickedInven();
	}
	else if (InChildName == TEXT("Btn_Gacha"))
	{
		VM->OnClickedGacha();
	}
	else if (InChildName == TEXT("Btn_Filter"))
	{
		VM->OnClickedFilter();
	}
	else if (InChildName == TEXT("Btn_GachaLog"))
	{
		VM->OnClickedGachaLog();
	}
}

void UHudLeftMenu::BindViewModel()
{
	Super::BindViewModel();
	
	VM = NewObject<UHudLeftVM>(this);
	VM->Init();
}