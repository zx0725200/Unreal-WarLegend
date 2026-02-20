// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "UIFlowPresenter.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UUIFlowPresenter : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
#pragma region Screen
	void OpenScreenTitle();
#pragma endregion Screen
	
#pragma region Popup
	void OpenPopupDungeonMenu();
#pragma endregion Popup
	
#pragma region Hud
	void OpenHudPlayerState();
#pragma endregion Hud
	
#pragma region ScreenEvent
	void HandleTitleConfirm();
#pragma endregion ScreenEvent
	
};
