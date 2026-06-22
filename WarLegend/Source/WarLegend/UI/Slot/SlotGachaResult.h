// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Core/SlotWidgetBase.h"
#include "SlotGachaResult.generated.h"

class UTextBlock;
class UWidgetAnimation;
class USlotGachaResultVM;

/**
 * 가챠 결과 TileView 엔트리. 자신의 등장 순서에 맞춰 지연 후 등장 연출을 재생한다.
 */
UCLASS()
class WARLEGEND_API USlotGachaResult : public USlotWidgetBase, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeDestruct() override;

private:
	void SetData();
	
	void RefreshGrade();
	void RefreshItemName();

	void ScheduleReveal(); // 등장 순서에 맞춰 연출 예약
	void PlayReveal();      // 실제 등장 연출 재생

private:
	UPROPERTY()
	TObjectPtr<USlotGachaResultVM> VM;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Grade;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ItemName;

	// 슬롯 한 칸당 연출 간격(초). 등장 순서 * 이 값 만큼 지연 후 재생된다.
	UPROPERTY(EditDefaultsOnly, Category="GachaResult")
	float RevealInterval = 0.15f;

	// UMG에서 만든 등장 연출 애니메이션. 위젯에 "Anim_Reveal" 이름으로 애니메이션을 추가하면 자동 바인딩된다.
	UPROPERTY(Transient, meta=(BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> Anim_Reveal;

	FTimerHandle RevealTimerHandle;
};
