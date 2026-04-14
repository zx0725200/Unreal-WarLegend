// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Core/SlotWidgetBase.h"
#include "SlotInventory.generated.h"

class UTextBlock;
class UImage;
struct FMyItem;

class USlotInventoryVM;
struct FGameplayTag;
struct FTestStruct;
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
};
