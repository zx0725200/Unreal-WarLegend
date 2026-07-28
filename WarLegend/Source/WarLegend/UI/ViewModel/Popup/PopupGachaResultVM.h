// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "PopupGachaResultVM.generated.h"

class USlotGachaResultVM;

/**
 * 가챠 결과 팝업 ViewModel. 가장 최근 뽑기 결과를 슬롯 VM 리스트로 만들어 TileView에 공급한다.
 */
UCLASS()
class WARLEGEND_API UPopupGachaResultVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	void OnRetry();

	const TArray<TObjectPtr<USlotGachaResultVM>>& GetItems() const { return ItemList; }

private:
	void BuildResultSlots();

private:
	UPROPERTY()
	TArray<TObjectPtr<USlotGachaResultVM>> ItemList;
};
