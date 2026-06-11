// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotItemInfo.h"

#include "Components/TextBlock.h"
#include "ETC/Define.h"
#include "ETC/Struct.h"

namespace
{
	const FLinearColor CompareUpColor = FLinearColor(0.3f, 1.f, 0.3f);
	const FLinearColor CompareDownColor = FLinearColor(1.f, 0.35f, 0.35f);
	const FLinearColor CompareSameColor = FLinearColor(0.6f, 0.6f, 0.6f);
}

void USlotItemInfo::SetData(const FMyItem& InItem) const
{
	Txt_Name->SetText(FText::FromString(InItem.ItemName));
	Txt_Name->SetColorAndOpacity(InItem.ItemGradeColor);

	Txt_Type->SetText(FText::FromString(InItem.ItemTypeName));

	Txt_HP->SetText(FText::AsNumber(InItem.HP));
	Txt_ATK->SetText(FText::AsNumber(InItem.ATK));
	Txt_DEF->SetText(FText::AsNumber(InItem.DEF));
}

void USlotItemInfo::SetCompareData(const int32 InHPDiff, const int32 InATKDiff, const int32 InDEFDiff) const
{
	Txt_HPCompare->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Txt_ATKCompare->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Txt_DEFCompare->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	SetCompareText(Txt_HPCompare, InHPDiff);
	SetCompareText(Txt_ATKCompare, InATKDiff);
	SetCompareText(Txt_DEFCompare, InDEFDiff);
}

void USlotItemInfo::HideCompare() const
{
	Txt_HPCompare->SetVisibility(ESlateVisibility::Collapsed);
	Txt_ATKCompare->SetVisibility(ESlateVisibility::Collapsed);
	Txt_DEFCompare->SetVisibility(ESlateVisibility::Collapsed);
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
