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

#pragma region Popup
	void OpenPopupGacha() const;
	void OpenPopupGachaFilter() const;
	void OpenPopupGachaLog() const;
#pragma endregion Popup

private:
	UPROPERTY()
	TObjectPtr<UGachaPresenter> GachaPresenter;
};
