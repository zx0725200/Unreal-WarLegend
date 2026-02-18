// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ScreenWidgetBase.h"
#include "ScreenTitle.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UScreenTitle : public UScreenWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
private:
	void OnClickedConfirm();
};
