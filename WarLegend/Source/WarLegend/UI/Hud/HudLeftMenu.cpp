// Fill out your copyright notice in the Description page of Project Settings.


#include "HudLeftMenu.h"
#include "UIFlowPresenter.h"

void UHudLeftMenu::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Inven"))
	{
		OnClickedInven();
	}
	else if (InChildName == TEXT("Btn_RollBack"))
	{
		OnClickedRollBack();
	}
	else if (InChildName == TEXT("Btn_Gacha"))
	{
		OnClickedGacha();
	}
	else if (InChildName == TEXT("Btn_Filter"))
	{
		OnClickedFilter();
	}
	else if (InChildName == TEXT("Btn_GachaLog"))
	{
		OnClickedGachaLog();
	}
}

void UHudLeftMenu::OnClickedInven()
{
	const auto UIPresenter = GTUIGetMgr(UUIFlowPresenter);
	if (!UIPresenter)
	{
		return;
	}
	
	UIPresenter->OpenScreenInventory();
}

void UHudLeftMenu::OnClickedGacha()
{
	const auto UIPresenter = GTUIGetMgr(UUIFlowPresenter);
	if (!UIPresenter)
	{
		return;
	}
	
	UIPresenter->OpenPopupGacha();
}

void UHudLeftMenu::OnClickedFilter()
{
	const auto UIPresenter = GTUIGetMgr(UUIFlowPresenter);
	if (!UIPresenter)
	{
		return;
	}
	
	UIPresenter->OpenPopupGachaFilter();
}

void UHudLeftMenu::OnClickedGachaLog()
{
	const auto UIPresenter = GTUIGetMgr(UUIFlowPresenter);
	if (!UIPresenter)
	{
		return;
	}
	
	UIPresenter->OpenPopupGachaLog();
}

void UHudLeftMenu::OnClickedRollBack()
{
	const auto UIPresenter = GTUIGetMgr(UUIFlowPresenter);
	if (!UIPresenter)
	{
		return;
	}
	
	UIPresenter->GotoCity();
}
