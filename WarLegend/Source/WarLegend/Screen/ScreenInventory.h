// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ScreenWidgetBase.h"
#include "ScreenInventory.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UScreenInventory : public UScreenWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
};
