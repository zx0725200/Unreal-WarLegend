// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WLUserWidgetBase.h"
#include "SlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotWidgetBase : public UWLUserWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	virtual EUserWidgetType GetUIType() const override { return EUserWidgetType::Slot; }
};
