// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/HudWidgetBase.h"
#include "HudLeftMenu.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UHudLeftMenu : public UHudWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void OnClickEvent(const FName& InChildName) override;
	
private:
	void OnClickedInven();
	void OnClickedGacha();
	void OnClickedFilter();
	void OnClickedGachaLog();
	void OnClickedRollBack();
};
