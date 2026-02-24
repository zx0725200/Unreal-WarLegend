// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ScreenWidgetBase.h"
#include "ScreenInventory.generated.h"

class USlotEquipItem;
class UVerticalBox;
class UScreenInventoryVM;
class UTileView;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UScreenInventory : public UScreenWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	void SetViewModel(UScreenInventoryVM* InData);
	void Init();
	
private:
	UPROPERTY(EditDefaultsOnly, Category="DungeonMenu")
	TSubclassOf<USlotEquipItem> EquipSlotClass;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTileView> TileView_Inventory;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> Vertical_Equip;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> Vertical_Boss;
	
	UPROPERTY()
	TObjectPtr<UScreenInventoryVM> VM;
};
