// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupDungeonMenu.generated.h"

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
	
	void Init(const TArray<UPopupDungeonMenuVM*>& InData);

private:
	UPROPERTY(EditDefaultsOnly, Category="DungeonMenu")
	TSubclassOf<USlotDungeonMenu> SlotClass;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> Vertical_DungeonMenu;
	
	UPROPERTY()
	TArray<TObjectPtr<USlotDungeonMenu>> DungeonSlots;
};
