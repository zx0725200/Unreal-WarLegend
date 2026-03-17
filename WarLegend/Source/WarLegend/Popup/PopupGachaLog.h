// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupGachaLog.generated.h"

class UHudGachaLogVM;
class UScrollBox;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupGachaLog : public UPopupWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	UFUNCTION()
	void StartHide();
	
	void SetViewModel(UHudGachaLogVM* InVM);
	void RefreshAll();

private:
	void OnClickedClear();
	
	void HandleLogUpdated();
	void HandleLogCleared();
	
	void StartAutoHide();
	
private:
	UPROPERTY()
	TObjectPtr<UHudGachaLogVM> VM;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> SB_Log;
	
	FTimerHandle HideTimerHandle;
};
