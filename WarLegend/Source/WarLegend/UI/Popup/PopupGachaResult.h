// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupGachaResult.generated.h"

class UTileView;
class UPopupGachaResultVM;

UCLASS()
class WARLEGEND_API UPopupGachaResult : public UPopupWidgetBase
{
	GENERATED_BODY()

public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void BindViewModel() override;
	virtual void OnClickEvent(const FName& InChildName) override;

private:
	void BuildResultSlots();

private:
	UPROPERTY()
	TObjectPtr<UPopupGachaResultVM> VM;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTileView> TileView_Result;
};
