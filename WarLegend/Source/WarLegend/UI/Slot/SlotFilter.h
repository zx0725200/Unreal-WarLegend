// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/SlotWidgetBase.h"
#include "SlotFilter.generated.h"

class USlotFilterVM;
class UTextBlock;
class UCheckBox;
/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotFilter : public USlotWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	void SetViewModel(USlotFilterVM* InVM);
	
private:
	void SetData();
	
	UFUNCTION()
	void OnCheckBoxChanged(bool bIsChecked);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> ChBox_Filter;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Filter;

	UPROPERTY()
	TObjectPtr<USlotFilterVM> VM;
};
