// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupGachaFilter.generated.h"

class UVerticalBox;
class UPopupGachaFilterVM;
class USlotFilterVM;
/**
 *
 */
UCLASS()
class WARLEGEND_API UPopupGachaFilter : public UPopupWidgetBase
{
	GENERATED_BODY()

public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	virtual void BindViewModel() override;

private:
	void BindVM();
	void UnbindVM();

	void HandleSlotListChanged(const TArray<TObjectPtr<USlotFilterVM>>& InSlotList);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VBox_Filter;

	UPROPERTY()
	TObjectPtr<UPopupGachaFilterVM> VM;
};

