// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "PopupGachaVM.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGachaCompleted);

UCLASS()
class WARLEGEND_API UPopupGachaVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	void OnGacha(const int32 InItemCount);

	FOnGachaCompleted& GetOnGachaCompleted() { return OnGachaCompleted; }

private:
	FOnGachaCompleted OnGachaCompleted;
};
