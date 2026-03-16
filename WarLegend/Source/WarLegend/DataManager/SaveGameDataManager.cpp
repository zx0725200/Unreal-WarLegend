// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameDataManager.h"

#include "DataAsset/WLSaveGame.h"
#include "ETC/Constant.h"
#include "ETC/Struct.h"
#include "Kismet/GameplayStatics.h"

void USaveGameDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	LoadData(Constant::SaveData);
}

void USaveGameDataManager::SetGachaFilter(const EItemGrade Grade, const bool bChecked)
{
	if (!SaveGameData) return;
    
	SaveGameData->GachaFilter.Add(Grade, bChecked);
	SaveGame(Constant::SaveData);
}

void USaveGameDataManager::SetInvenData(const int32 InItemID, const FMyItem& InData)
{
	if (!SaveGameData) return;
	
	SaveGameData->InvenItemData.Add(InItemID, InData);
	SaveGame(Constant::SaveData);
}

void USaveGameDataManager::SaveGame(const FString& InSaveName)
{
	if (!SaveGameData) return;
	
	UGameplayStatics::SaveGameToSlot(SaveGameData, InSaveName, 0);
}

void USaveGameDataManager::LoadData(const FString& InSaveName)
{
	if (UGameplayStatics::DoesSaveGameExist(InSaveName, 0))
	{
		SaveGameData = Cast<UWLSaveGame>(UGameplayStatics::LoadGameFromSlot(InSaveName, 0));
	}

	// 세이브 파일 없거나 캐스트 실패 시 새로 생성
	if (!SaveGameData)
	{
		SaveGameData = Cast<UWLSaveGame>(UGameplayStatics::CreateSaveGameObject(UWLSaveGame::StaticClass()));
	}
}
