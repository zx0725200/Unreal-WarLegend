// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "PopupDungeonMenuVM.generated.h"

class USlotDungeonVM;
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPageChanged,
	const TArray<USlotDungeonVM*>& /*SlotList*/,
	int32 /*CurrentPage*/,
	int32 /*MaxPage*/);
/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupDungeonMenuVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void NotifyAll() override;
	
	void OnNextPage();
	void OnPrevPage();
	void OnChangePage(int32 NewPage);

	FOnPageChanged& GetOnPageChanged() { return OnPageChanged; }
	
private:
	const TArray<USlotDungeonVM*>& GetCurrentSlotList() const;
	int32 GetMaxPage() const;
	
private:
	UPROPERTY()
	TArray<TObjectPtr<USlotDungeonVM>> SlotDungeonVMList;
	
	int32 CurrentPageIndex = 1;
	
	FOnPageChanged OnPageChanged;
};
