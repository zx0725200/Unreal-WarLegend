// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupItemInfoVM.h"

#include "InventoryManager.h"
#include "ETC/Define.h"

void UPopupItemInfoVM::Init()
{
	Super::Init();
	
	UInventoryManager* InvenMgr = GetInvenManager();
	VALID_RETURN(InvenMgr);
	
	SelectedItemData = InvenMgr->GetSelectedItemData();
}
