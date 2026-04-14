// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ViewModelBase.generated.h"

class UInventoryManager;
class UTableManager;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UViewModelBase : public UObject
{
	GENERATED_BODY()
	
protected:
	virtual void Init();
	
	virtual UWorld* GetMyWorld() const;
	virtual UTableManager* GetTableManager() const;
	virtual UInventoryManager* GetInvenManager() const;
};
