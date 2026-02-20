// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/SlotWidgetBase.h"
#include "SlotDungeonMenu.generated.h"

class UPopupDungeonMenuVM;
class UTextBlock;
struct FDungeonTableData;
/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotDungeonMenu : public USlotWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	void SetData(const UPopupDungeonMenuVM* InData);
	
private:
	void SetDungeonName(const UPopupDungeonMenuVM* InData);
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Name;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Level;
};
