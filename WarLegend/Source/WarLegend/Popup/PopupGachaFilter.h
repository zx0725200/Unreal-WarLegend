// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupGachaFilter.generated.h"

class UVerticalBox;
class UPopupGachaFilterVM;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupGachaFilter : public UPopupWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	void SetViewModel(UPopupGachaFilterVM* InVM);

private:
	void RefreshSlots();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Slots;

	UPROPERTY()
	TObjectPtr<UPopupGachaFilterVM> VM;
};
