// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameDataManager.generated.h"

struct FMyItem;
enum class EItemGrade : uint8;
class UWLSaveGame;
/**
 * 
 */
UCLASS()
class WARLEGEND_API USaveGameDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SetGachaFilter(const EItemGrade InGrade, const bool bChecked);
	void SetInvenData(const int32 InItemID, const FMyItem& InData);
	
	void SaveGame(const FString& InSaveName);
	UWLSaveGame* GetSaveGame() const { return SaveGameData; }

private:
	void LoadData(const FString& InSaveName);

private:
	UPROPERTY()
	TObjectPtr<UWLSaveGame> SaveGameData;
};
