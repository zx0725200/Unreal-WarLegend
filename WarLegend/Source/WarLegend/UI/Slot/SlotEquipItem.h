// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/SlotWidgetBase.h"
#include "SlotEquipItem.generated.h"

class UTextBlock;
enum class EItemType : uint8;
/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotEquipItem : public USlotWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	void SetData(const EItemType InItemType, const FString& InItemName);
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Name;
};
