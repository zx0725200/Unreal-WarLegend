// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "ETC/Struct.h"
#include "PopupGachaLogVM.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLogAdded, const FGachaLogData&);
DECLARE_MULTICAST_DELEGATE(FOnLogCleared);

UCLASS()
class WARLEGEND_API UPopupGachaLogVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void NotifyAll() override;
	virtual void ClearBinding() override;

	void ClearAll();

	const TArray<FGachaLogData>& GetLogList() const;

	FOnLogAdded& GetOnLogAdded() { return OnLogAdded; }
	FOnLogCleared& GetOnLogCleared() { return OnLogCleared; }

private:
	void HandleLogAdded(const FGachaLogData& InData);
	void HandleLogCleared();

private:
	FOnLogAdded OnLogAdded;
	FOnLogCleared OnLogCleared;
};
