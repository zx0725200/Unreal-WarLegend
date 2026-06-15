// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "PopupItemDiscardVM.generated.h"

class USlotFilterVM;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDiscardSlotListChanged, const TArray<TObjectPtr<USlotFilterVM>>&);

/**
 * 인벤토리 "모두 버리기" 대상 등급을 설정하는 팝업의 ViewModel.
 * 가챠 필터 팝업과 동일하게 SlotFilter 체크박스를 재사용하되, 체크 상태는 DiscardFilter에 저장된다.
 */
UCLASS()
class WARLEGEND_API UPopupItemDiscardVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void NotifyAll() override;

	const TArray<TObjectPtr<USlotFilterVM>>& GetSlotVMList() const { return SlotVMList; }

	FOnDiscardSlotListChanged& GetOnSlotListChanged() { return OnSlotListChanged; }

private:
	UPROPERTY()
	TArray<TObjectPtr<USlotFilterVM>> SlotVMList;

	FOnDiscardSlotListChanged OnSlotListChanged;
};
