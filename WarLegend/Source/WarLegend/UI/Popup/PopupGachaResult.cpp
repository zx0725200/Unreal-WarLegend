// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupGachaResult.h"

#include "Components/TileView.h"
#include "ETC/Define.h"
#include "ViewModel/Popup/PopupGachaResultVM.h"
#include "ViewModel/Slot/SlotGachaResultVM.h"

void UPopupGachaResult::Awake()
{
	Super::Awake();
}

void UPopupGachaResult::OnEnable()
{
	Super::OnEnable();
}

void UPopupGachaResult::OnDisable()
{
	Super::OnDisable();
	VALID_RETURN(VM);

	VM->ClearBinding();
	VM = nullptr;
}

void UPopupGachaResult::BindViewModel()
{
	Super::BindViewModel();

	VM = NewObject<UPopupGachaResultVM>(this);
	VM->Init();

	BuildResultSlots();
}

void UPopupGachaResult::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Retry"))
	{
		VALID_RETURN(VM);
		VM->OnRetry();
		BuildResultSlots(); // 재시도 결과로 TileView 다시 채운다.
	}
}

void UPopupGachaResult::BuildResultSlots()
{
	VALID_RETURN(VM);
	TileView_Result->ClearListItems();
	
	for (USlotGachaResultVM* SlotVM : VM->GetItems())
	{
		TileView_Result->AddItem(SlotVM); // 엔트리(USlotGachaResult)가 순서대로 등장 연출을 재생한다.
	}
}
