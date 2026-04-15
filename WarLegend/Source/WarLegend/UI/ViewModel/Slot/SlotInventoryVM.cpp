// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotInventoryVM.h"

#include "UIManagerImpl.h"
#include "ETC/Define.h"

void USlotInventoryVM::Init(const FMyItem& InData)
{
	MyItem = InData;
}

void USlotInventoryVM::OnOpenItemInfo()
{
	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);
	
	UIMgr->ShowUI(TEXT("PopupItemInfo"));
}
