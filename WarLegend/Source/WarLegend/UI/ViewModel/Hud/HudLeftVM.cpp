// Fill out your copyright notice in the Description page of Project Settings.


#include "HudLeftVM.h"

#include "UIManagerImpl.h"
#include "ETC/Define.h"

void UHudLeftVM::Init()
{
	Super::Init();
}

void UHudLeftVM::OnClickedInven()
{
	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);
	
	UIMgr->ShowUI(TEXT("ScreenInventory"));
}

void UHudLeftVM::OnClickedGacha()
{
	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);
	
	UIMgr->ShowUI(TEXT("PopupGacha"));
}

void UHudLeftVM::OnClickedFilter()
{
}

void UHudLeftVM::OnClickedGachaLog()
{
}

void UHudLeftVM::OnClickedRollBack()
{
}
