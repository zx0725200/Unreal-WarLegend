// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupCharacterSelect.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupCharacterSelect : public UPopupWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
};
