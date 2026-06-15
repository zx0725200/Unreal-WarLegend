// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Core/SlotWidgetBase.h"
#include "SlotInventory.generated.h"

class UTextBlock;
class UImage;
class USlotInventoryVM;

struct FMyItem;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotInventory : public USlotWidgetBase, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeDestruct() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
private:
	void SetData() const;
	void RefreshUpgradeMark() const;

	void OnClickedSlot();
	
	void SetSelectedState();
	void SetNormalState();
	
	UFUNCTION()
	void HandleClickedSlot(FGameplayTag InTag, const FMyItem& InItem);
	
private:
	UPROPERTY()
	TObjectPtr<USlotInventoryVM> VM;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Img_NotSelect;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Img_Select;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Name;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Grade;

	// 장착템보다 능력치 합이 높을 때만 표시되는 업그레이드 화살표(▲).
	// WBP에 아직 없어도 되도록 Optional 바인딩.
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> Txt_Upgrade;
};
