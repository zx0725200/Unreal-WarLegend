// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "UIFlowPresenter.generated.h"

class UGachaPresenter;
class UInventoryPresenter;
class UDungeonPresenter;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UUIFlowPresenter : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;
	
	void HandleEscClick();
	
#pragma region Screen
	void OpenScreenTitle();
	void OpenScreenInventory();
#pragma endregion Screen
	
#pragma region Popup
	void OpenPopupDungeonMenu() const;
	void OpenPopupGacha() const;
#pragma endregion Popup
	
#pragma region Hud
	
#pragma endregion Hud
	
#pragma region ScreenEvent
	void HandleTitleConfirm();
#pragma endregion ScreenEvent
	
#pragma region PopupEvent
	void HandleSlotDungeonMenuClick(int32 InSlotIndex);
#pragma endregion PopupEvent
	
private:
	UPROPERTY()
	TObjectPtr<UDungeonPresenter> DungeonPresenter;
	
	UPROPERTY()
	TObjectPtr<UInventoryPresenter> InventoryPresenter;
	
	UPROPERTY()
	TObjectPtr<UGachaPresenter> GachaPresenter;
};
