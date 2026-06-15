// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "ETC/Struct.h"
#include "SlotItemInfoVM.generated.h"

// 아이템 정보 슬롯이 보여줄 표시 모드
enum class EItemInfoMode : uint8
{
	Compare,	// 장착템 대비 능력치 차이를 ▲/▼/- 로 표시
	Equipped	// "[장착중]" 뱃지를 표시
};

/**
 * 아이템 정보 슬롯(USlotItemInfo) 하나가 들고 있는 데이터.
 */
UCLASS()
class WARLEGEND_API USlotItemInfoVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	void SetItem(const FMyItem& InItem);

	// 비교 모드로 설정 (선택 슬롯이 장착 중이 아닐 때)
	void SetCompare(const int32 InHPDiff, const int32 InATKDiff, const int32 InDEFDiff);

	// 장착중 모드로 설정
	void SetEquipped();

	const FMyItem& GetItem() const { return ItemData; }
	EItemInfoMode GetMode() const { return Mode; }

	int32 GetHPDiff() const { return HPDiff; }
	int32 GetATKDiff() const { return ATKDiff; }
	int32 GetDEFDiff() const { return DEFDiff; }

private:
	FMyItem ItemData;

	int32 HPDiff = 0;
	int32 ATKDiff = 0;
	int32 DEFDiff = 0;

	EItemInfoMode Mode = EItemInfoMode::Compare;
};
