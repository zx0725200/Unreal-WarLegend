// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "HudMainVM.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UHudMainVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
};
