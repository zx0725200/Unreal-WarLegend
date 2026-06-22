// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotItemInfo.h"

#include "Components/TextBlock.h"
#include "ETC/Define.h"
#include "ETC/Struct.h"
#include "ViewModel/Slot/SlotItemInfoVM.h"

namespace
{
	const FLinearColor CompareUpColor = FLinearColor(0.3f, 1.f, 0.3f);
	const FLinearColor CompareDownColor = FLinearColor(1.f, 0.35f, 0.35f);
	const FLinearColor CompareSameColor = FLinearColor(0.6f, 0.6f, 0.6f);
}

void USlotItemInfo::SetViewModel(USlotItemInfoVM* InVM)
{
	VM = InVM;

	RefreshUI();
}

void USlotItemInfo::RefreshUI() const
{
	VALID_RETURN(VM);

	SetItemData(VM->GetItem());

	// 모드에 따라 "장착중" 뱃지 또는 비교 화살표 중 하나만 보여준다.
	if (VM->GetMode() == EItemInfoMode::Equipped)
	{
		SetEquipped(true);
		HideCompare();
	}
	else
	{
		SetEquipped(false);
		ShowCompare();
	}
}

void USlotItemInfo::SetItemData(const FMyItem& InItem) const
{
	Txt_Name->SetText(FText::FromString(InItem.ItemName));
	Txt_Name->SetColorAndOpacity(InItem.ItemGradeColor);

	Txt_Type->SetText(FText::FromString(InItem.ItemTypeName));
	Txt_Type->SetColorAndOpacity(InItem.ItemGradeColor);

	// 어떤 스탯인지 알 수 있게 앞에 라벨을 붙인다.
	Txt_HP->SetText(FText::FromString(FString::Printf(TEXT("HP %d"), InItem.HP)));
	Txt_ATK->SetText(FText::FromString(FString::Printf(TEXT("ATK %d"), InItem.ATK)));
	Txt_DEF->SetText(FText::FromString(FString::Printf(TEXT("DEF %d"), InItem.DEF)));
}

void USlotItemInfo::ShowCompare() const
{
	VALID_RETURN(VM);

	Txt_HPCompare->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Txt_ATKCompare->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Txt_DEFCompare->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	SetCompareText(Txt_HPCompare, VM->GetHPDiff());
	SetCompareText(Txt_ATKCompare, VM->GetATKDiff());
	SetCompareText(Txt_DEFCompare, VM->GetDEFDiff());
}

void USlotItemInfo::HideCompare() const
{
	Txt_HPCompare->SetVisibility(ESlateVisibility::Collapsed);
	Txt_ATKCompare->SetVisibility(ESlateVisibility::Collapsed);
	Txt_DEFCompare->SetVisibility(ESlateVisibility::Collapsed);
}

void USlotItemInfo::SetEquipped(const bool bEquipped) const
{
	if (bEquipped)
	{
		Txt_State->SetText(FText::FromString(TEXT("[장착중]")));
		// 흰 배경에서도 잘 보이고 업그레이드 화살표(초록)와 구분되도록 진한 보라색으로 표시
		Txt_State->SetColorAndOpacity(FLinearColor(0.55f, 0.1f, 0.85f));
		Txt_State->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Txt_State->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USlotItemInfo::SetCompareText(UTextBlock* InText, const int32 InDiff) const
{
	VALID_RETURN(InText);

	if (InDiff > 0)
	{
		InText->SetText(FText::FromString(FString::Printf(TEXT("▲ +%d"), InDiff)));
		InText->SetColorAndOpacity(CompareUpColor);
	}
	else if (InDiff < 0)
	{
		InText->SetText(FText::FromString(FString::Printf(TEXT("▼ %d"), InDiff)));
		InText->SetColorAndOpacity(CompareDownColor);
	}
	else
	{
		InText->SetText(FText::FromString(TEXT("-")));
		InText->SetColorAndOpacity(CompareSameColor);
	}
}
