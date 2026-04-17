// Fill out your copyright notice in the Description page of Project Settings.


#include "HudMainVM.h"
#include "UIManagerImpl.h"
#include "ETC/Define.h"

void UHudMainVM::Init()
{
	Super::Init();
	
	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);
	
	UIMgr->ShowUI(TEXT("HudLeftMenu"));
}
