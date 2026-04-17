// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupDungeonMenu.generated.h"

class USlotDungeonVM;
class UTextBlock;
class UPopupDungeonMenuVM;
class USlotDungeonMenu;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupDungeonMenu : public UPopupWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	virtual void BindViewModel() override;

private:
	void InitSlotPool();
	
	void BindVM();
	void UnbindVM();

	void OnPageChanged(const TArray<USlotDungeonVM*>& InSlotList, const int32 InCurrentPage, const int32 InMaxPage);

private:
	UPROPERTY()
	TObjectPtr<UPopupDungeonMenuVM> VM;
	
	UPROPERTY()
	TArray<TObjectPtr<USlotDungeonMenu>> PooledSlots;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> Vertical_DungeonMenu;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Page;
};
