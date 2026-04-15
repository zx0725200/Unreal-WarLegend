// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ViewModelBase.generated.h"

class USaveGameDataManager;
class UGachaManager;
class UUIManagerImpl;
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
	
	UTableManager* GetTableManager() const;
	UInventoryManager* GetInvenManager() const;
	UUIManagerImpl* GetUIManager() const;
	UGachaManager* GetGachaManager() const;
	USaveGameDataManager* GetSaveGameDataManager() const;
	
private:
	UWorld* GetMyWorld() const;
	UGameInstance* GetGameInstance() const;
	ULocalPlayer* GetLocalPlayer() const;
};
