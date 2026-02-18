// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PopupWidgetBase.h"

#include "Character/WarLegendPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UPopupWidgetBase::Awake()
{
	Super::Awake();
}

void UPopupWidgetBase::OnEnable()
{
	Super::OnEnable();
	
	LockPlayerInput();
}

void UPopupWidgetBase::OnDisable()
{
	Super::OnDisable();
	
	UnlockPlayerInput();
}

void UPopupWidgetBase::OnDestroy()
{
	Super::OnDestroy();
}

void UPopupWidgetBase::Update(const float InDeltaTime)
{
	Super::Update(InDeltaTime);
}

void UPopupWidgetBase::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Exit"))
	{
		Hide();
	}
}

void UPopupWidgetBase::LockPlayerInput() const
{
	AWarLegendPlayerController* PlayerController =  Cast<AWarLegendPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PlayerController)
	{
		return;
	}
	
	FInputModeUIOnly UIOnlyMode;
	PlayerController->SetInputMode(UIOnlyMode);
}

void UPopupWidgetBase::UnlockPlayerInput() const
{
	AWarLegendPlayerController* PlayerController =  Cast<AWarLegendPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PlayerController)
	{
		return;
	}
	
	FInputModeGameAndUI InputGameMode;
	PlayerController->SetInputMode(InputGameMode);
}
