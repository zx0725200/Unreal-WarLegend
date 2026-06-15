// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/SlotWidgetBase.h"
#include "SlotItemInfo.generated.h"

class UTextBlock;
class USlotItemInfoVM;
struct FMyItem;
/**
 * 아이템 정보(이름/타입/능력치) 한 칸을 표시하는 슬롯.
 * PopupItemInfo에서 선택 아이템 / 장착 아이템 두 개를 나란히 보여줄 때 사용한다.
 */
UCLASS()
class WARLEGEND_API USlotItemInfo : public USlotWidgetBase
{
	GENERATED_BODY()

public:
	void SetViewModel(USlotItemInfoVM* InVM);

private:
	void RefreshUI() const;

	void SetItemData(const FMyItem& InItem) const;

	// 비교 대상과의 능력치 차이를 ▲/▼/- 로 표시한다.
	void ShowCompare() const;
	void HideCompare() const;

	// "장착중" 표시를 켜고 끈다.
	void SetEquipped(const bool bEquipped) const;

	void SetCompareText(UTextBlock* InText, const int32 InDiff) const;

private:
	UPROPERTY()
	TObjectPtr<USlotItemInfoVM> VM;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Name;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Type;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_HP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ATK;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_DEF;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_HPCompare;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ATKCompare;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_DEFCompare;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_State;
};
