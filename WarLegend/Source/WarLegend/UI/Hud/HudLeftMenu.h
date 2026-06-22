// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/HudWidgetBase.h"
#include "HudLeftMenu.generated.h"

class UHudLeftVM;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UHudLeftMenu : public UHudWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	virtual void BindViewModel() override;

private:
	UPROPERTY()
	TObjectPtr<UHudLeftVM> VM;
};
