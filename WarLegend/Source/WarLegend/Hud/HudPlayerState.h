// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/HudWidgetBase.h"
#include "HudPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UHudPlayerState : public UHudWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
};
