// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Core/HudWidgetBase.h"
#include "HudMonsterHeadUp.generated.h"

class UHudMonsterHeadUpVM;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UHudMonsterHeadUp : public UHudWidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	void SetViewModel(UHudMonsterHeadUpVM* InVM);

private:
	void OnLapCountUpdated(const int32 NewCount);
 
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Count;
 
	UPROPERTY()
	TObjectPtr<UHudMonsterHeadUpVM> VM;
};
