// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WLUserWidgetBase.h"
#include "ScreenWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UScreenWidgetBase : public UWLUserWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override; 
	
	virtual EUserWidgetType GetUIType() const override { return EUserWidgetType::Screen; }
	
};
