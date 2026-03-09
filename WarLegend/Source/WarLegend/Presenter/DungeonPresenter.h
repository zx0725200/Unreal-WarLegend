// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DungeonPresenter.generated.h"

class UTableManager;
class UUIManagerImpl;
class UPopupDungeonMenuVM;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UDungeonPresenter : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(UUIManagerImpl* InUIMgr, UTableManager* InTableMgr);
	
	void OpenPopupDungeonMenu();

private:
	void HandleSlotDungeonMenuClick(int32 InSlotIndex);
	
private:
	TArray<TObjectPtr<UPopupDungeonMenuVM>> VMList;
	
	UPROPERTY()
	TObjectPtr<UUIManagerImpl> UIMgr;

	UPROPERTY()
	TObjectPtr<UTableManager> TableMgr;
};
