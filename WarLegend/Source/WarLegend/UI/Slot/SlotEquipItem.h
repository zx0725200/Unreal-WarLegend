// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/SlotWidgetBase.h"
#include "ETC/Enum.h"
#include "SlotEquipItem.generated.h"

class UTextBlock;
class USlotEquipItemVM;
struct FMyItem;
struct FGameplayTag;
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
	void RefreshEquipped() const;

	// 장착 슬롯 클릭 시 해당 장착 아이템 정보 팝업을 연다.
	void OnClickedSlot();

	UFUNCTION()
	void HandleEquipChanged(FGameplayTag InTag, const FMyItem& InItem);

private:
	UPROPERTY()
	TObjectPtr<USlotEquipItemVM> VM;

	// 슬롯 타입명 (무기/방어구 등)
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Name;

	// 장착 중인 아이템명
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ItemName;
};
