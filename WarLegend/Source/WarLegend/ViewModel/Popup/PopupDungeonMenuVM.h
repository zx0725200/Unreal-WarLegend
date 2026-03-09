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
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmRequested, int32);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnNameChanged,     const FString&);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelChanged,   int32, int32); // Min, Max

	FOnConfirmRequested OnConfirmRequested;
	FOnNameChanged      OnNameChanged;
	FOnLevelChanged     OnLevelChanged;
	
	int32          GetID()				const { return ID; }
	const FString& GetDungeonName()     const { return Name; }
	int32          GetMinLevel()		const { return MinLevel; }
	int32          GetMaxLevel()		const { return MaxLevel; }
	
	void SetName(const FString& InName)
	{
		Name = InName;
		OnNameChanged.Broadcast(Name);
	}

	void SetLevel(const int32 InMin, const int32 InMax)
	{
		MinLevel = InMin;
		MaxLevel = InMax;
		OnLevelChanged.Broadcast(MinLevel, MaxLevel);
	}

	void SetID(const int32 InID) { ID = InID; }

	UFUNCTION()
	void Confirm() const { OnConfirmRequested.Broadcast(ID); }

private:
	UPROPERTY()
	int32 ID = 0;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 MinLevel = 0;

	UPROPERTY()
	int32 MaxLevel = 0;
};
