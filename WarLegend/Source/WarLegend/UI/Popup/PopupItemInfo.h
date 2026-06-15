// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupItemInfo.generated.h"

class UTextBlock;
class USlotItemInfo;
class UPopupItemInfoVM;
/**
 *
 */
UCLASS()
class WARLEGEND_API UPopupItemInfo : public UPopupWidgetBase
{
	GENERATED_BODY()

public:
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	virtual void BindViewModel() override;

private:
	void SetViewModel(UPopupItemInfoVM* InVM);

	void RefreshUI() const;
	void RefreshSelectedSlot() const;
	void RefreshEquippedSlot() const;
	void RefreshEquipButton() const;

	void OnClickedEquip();

private:
	UPROPERTY()
	TObjectPtr<UPopupItemInfoVM> VM;

	// 선택한 아이템 정보 (장착 아이템과의 비교 표시 포함)
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USlotItemInfo> Slot_Selected;

	// 현재 장착 중인 아이템 정보 (없으면 숨김)
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USlotItemInfo> Slot_Equipped;

	// 장착/해제 버튼 라벨 (WBP에 없어도 되도록 Optional 바인딩)
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> Txt_Equip;
};
