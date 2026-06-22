// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HudWidgetBase.h"
#include "HudBossHp.generated.h"

class UProgressBar;
class UHudBossHpVM;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UHudBossHp : public UHudWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void OnDisable() override;
	virtual void BindViewModel() override;

private:
	void BindVM();
	void UnbindVM();
	
	UFUNCTION()
	void OnHpRatioChanged(const float InNewRatio);

private:
	UPROPERTY()
	TObjectPtr<UHudBossHpVM> VM;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HpProgressBar;
};
