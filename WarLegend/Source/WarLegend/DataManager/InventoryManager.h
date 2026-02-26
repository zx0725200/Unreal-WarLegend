// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "InventoryManager.generated.h"

class USlotInventoryVM;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UInventoryManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	const TArray<TObjectPtr<USlotInventoryVM>>& GetInventoryItemData() const { return InventoryItemData; }
	
private:
	UPROPERTY()
	TArray<TObjectPtr<USlotInventoryVM>> InventoryItemData;
};
