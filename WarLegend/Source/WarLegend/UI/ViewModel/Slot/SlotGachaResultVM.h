// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "ETC/Struct.h"
#include "SlotGachaResultVM.generated.h"

/**
 * 가챠 결과 TileView의 한 칸을 표현하는 ViewModel.
 */
UCLASS()
class WARLEGEND_API USlotGachaResultVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	void SetData(const FGachaLogData& InData, const int32 InRevealOrder);

	const FGachaLogData& GetData() const { return Data; }
	int32 GetRevealOrder() const { return RevealOrder; } // 등장(연출) 순서

private:
	FGachaLogData Data;
	int32 RevealOrder = 0;
};
