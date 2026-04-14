// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupGachaLog.generated.h"

class UUMyButton;
class USlotGachaLog;
struct FGachaLogData;
class UPopupGachaLogVM;
class UScrollBox;
/**
 * 
 */
UENUM()
enum class EGachaLogDisplayMode : uint8
{
	Toast,
	Full,
};

UCLASS()
class WARLEGEND_API UPopupGachaLog : public UPopupWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	void SetViewModel(UPopupGachaLogVM* InVM);
	void ShowAsToast();
	void ShowAsFull();

private:
	UFUNCTION()
	void StartHide();
	void StartHideTimer();
	
	void CreateLogSlot() const;
	void ApplyDisplayMode(EGachaLogDisplayMode InMode);
	
	void OnClickedClear();

private:
	UPROPERTY()
	TObjectPtr<UPopupGachaLogVM> VM;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> SB_Log;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UUMyButton> Btn_Exit;
	
	FTimerHandle HideTimerHandle;
};
