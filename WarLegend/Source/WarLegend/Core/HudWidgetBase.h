// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WLUserWidgetBase.h"
#include "HudWidgetBase.generated.h"

/**
 * Hud를 사용 할 때 베이스가 되는 위젯 입니다.
 */
UCLASS()
class WARLEGEND_API UHudWidgetBase : public UWLUserWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;
	virtual void Update(const float InDeltaTime) override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	virtual EUserWidgetType GetUIType() const override { return EUserWidgetType::Hud; }
	
};
