// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopupDungeonMenuVM.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UPopupDungeonMenuVM : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	int32 ID = 0;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MinLevel;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MaxLevel;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmRequested, int32);
	FOnConfirmRequested OnConfirmRequested;

	UFUNCTION()
	void Confirm() const
	{
		OnConfirmRequested.Broadcast(ID);
	}
};
