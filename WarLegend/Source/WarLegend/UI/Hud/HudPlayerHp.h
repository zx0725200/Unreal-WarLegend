// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HudWidgetBase.h"
#include "HudPlayerHp.generated.h"

class UProgressBar;
class UHudPlayerHpVM;
/**
 *
 */
UCLASS()
class WARLEGEND_API UHudPlayerHp : public UHudWidgetBase
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
	TObjectPtr<UHudPlayerHpVM> VM;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HpProgressBar;
};
