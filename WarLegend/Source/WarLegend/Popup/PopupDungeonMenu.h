// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupDungeonMenu.generated.h"

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
	
	void SetViewModel(const TArray<UPopupDungeonMenuVM*>& InData) { VM = InData; }
	
	void Init();
	void InitSlotPool();

private:
	void RefreshPage();
	void RefreshPageText() const;
	
	void OnClickedNext();
	void OnClickedPrev();
	
	int32 GetMaxPageIndex() const;

private:
	UPROPERTY()
	TArray<TObjectPtr<UPopupDungeonMenuVM>> VM;
	
	UPROPERTY()
	TArray<TObjectPtr<USlotDungeonMenu>> PooledSlots;
	
	UPROPERTY()
	int32 CurrentPageIndex = 1;
	
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> Vertical_DungeonMenu;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Page;
};
