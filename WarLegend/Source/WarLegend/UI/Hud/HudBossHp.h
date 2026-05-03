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
	virtual void NativeDestruct() override;
	virtual void BindViewModel() override;
	
private:
	void BindVM();
	void UnbindVM();
	
	void SetViewModel(UHudBossHpVM* InViewModel);
	
	UFUNCTION()
	void OnHpRatioChanged(float NewRatio);

private:
	UPROPERTY()
	TObjectPtr<UHudBossHpVM> VM;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HpProgressBar;
};
