// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupItemDiscard.generated.h"

class UVerticalBox;
class UPopupItemDiscardVM;
class USlotFilterVM;
/**
 * 인벤토리 "모두 버리기" 대상 등급을 설정하는 팝업.
 */
UCLASS()
class WARLEGEND_API UPopupItemDiscard : public UPopupWidgetBase
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
	TObjectPtr<UPopupItemDiscardVM> VM;
};
