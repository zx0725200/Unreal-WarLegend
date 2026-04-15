// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "HudLeftVM.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UHudLeftVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
	void OnClickedInven();
	void OnClickedGacha();
	void OnClickedFilter();
	void OnClickedGachaLog();
	void OnClickedRollBack();
};
