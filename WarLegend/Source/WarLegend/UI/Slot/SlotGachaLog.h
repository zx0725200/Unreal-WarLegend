// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/SlotWidgetBase.h"
#include "SlotGachaLog.generated.h"

class UTextBlock;
struct FGachaLogData;
/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotGachaLog : public USlotWidgetBase
{
	GENERATED_BODY()
	
public:
	void Init(const FGachaLogData& InData);
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Grade;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ItemName;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Time;
};
