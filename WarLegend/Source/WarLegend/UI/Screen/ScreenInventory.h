// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ScreenWidgetBase.h"
#include "ScreenInventory.generated.h"

enum class EItemType : uint8;
class USlotEquipItem;
class UTextBlock;
class UVerticalBox;
class UScreenInventoryVM;
class UTileView;
struct FMyItem;
struct FGameplayTag;
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
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override; 

protected:
	virtual void BindViewModel() override;
	
private:
	void SetViewModel(UScreenInventoryVM* InData);
	
	void InitEquipSlots();
	void InitInventorySlots();
	void RefreshTotalStats() const;

	void CreateEquipSlots(UVerticalBox* InParent, const TMap<EItemType, FString>& InItemData) const;

	void OnClickedReset();

	UFUNCTION()
	void HandleEquipChanged(FGameplayTag InTag, const FMyItem& InItem);

private:
	UPROPERTY(EditDefaultsOnly, Category="DungeonMenu")
	TSubclassOf<USlotEquipItem> EquipSlotClass;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTileView> TileView_Inventory;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> Vertical_Equip;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> Vertical_Boss;

	// 장착 아이템 능력치 합산 표시
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_TotalHP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_TotalATK;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_TotalDEF;

	UPROPERTY()
	TObjectPtr<UScreenInventoryVM> VM;
};
