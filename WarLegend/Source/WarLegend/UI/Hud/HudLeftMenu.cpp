// Fill out your copyright notice in the Description page of Project Settings.


#include "HudLeftMenu.h"
#include "UIFlowPresenter.h"
#include "Hud/HudLeftVM.h"

void UHudLeftMenu::OnClickEvent(const FName& InChildName)
{
	VALID_RETURN(VM);
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Inven"))
	{
		VM->OnClickedInven();
	}
	else if (InChildName == TEXT("Btn_RollBack"))
	{
		VM->OnClickedRollBack();
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
	
	auto* HudLeftVM = NewObject<UHudLeftVM>(this);
	HudLeftVM->Init();
	
	SetViewModel(HudLeftVM);
}

void UHudLeftMenu::SetViewModel(UHudLeftVM* InVM)
{
	VM = InVM;
}

// void UHudLeftMenu::OnClickedInven()
// {
// 	VALID_RETURN(VM);
// 	VM->OnClickedInven();
// }
//
// void UHudLeftMenu::OnClickedGacha()
// {
// 	VALID_RETURN(VM);
// 	VM->OnClickedGacha();
// 	
// 	const auto UIPresenter = GTUIGetMgr(UUIFlowPresenter);
// 	if (!UIPresenter)
// 	{
// 		return;
// 	}
// 	
// 	UIPresenter->OpenPopupGacha();
// }
//
// void UHudLeftMenu::OnClickedFilter()
// {
// 	VALID_RETURN(VM);
// 	VM->OnClickedFilter();
// 	
// 	const auto UIPresenter = GTUIGetMgr(UUIFlowPresenter);
// 	if (!UIPresenter)
// 	{
// 		return;
// 	}
// 	
// 	UIPresenter->OpenPopupGachaFilter();
// }
//
// void UHudLeftMenu::OnClickedGachaLog()
// {
// 	VALID_RETURN(VM);
// 	VM->OnClickedFilter();
// 	
// 	const auto UIPresenter = GTUIGetMgr(UUIFlowPresenter);
// 	if (!UIPresenter)
// 	{
// 		return;
// 	}
// 	
// 	UIPresenter->OpenPopupGachaLog();
// }
//
// void UHudLeftMenu::OnClickedRollBack()
// {
// 	const auto UIPresenter = GTUIGetMgr(UUIFlowPresenter);
// 	if (!UIPresenter)
// 	{
// 		return;
// 	}
// 	
// 	UIPresenter->GotoCity();
// }
