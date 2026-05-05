// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"

#include "SaveGameDataManager.h"
#include "TableManager.h"
#include "UIManager.h"
#include "UIManagerImpl.h"
#include "DataAsset/WLSaveGame.h"
#include "DataTable/ItemTableData.h"
#include "ETC/Constant.h"
#include "ETC/Define.h"
#include "ETC/Struct.h"

void UInventoryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	LoadData();
}

FMyItem UInventoryManager::GetSelectedItemData()
{
	const FMyItem* Found = InventoryItemData.FindByPredicate([this](const FMyItem& Item)
	{
	   return Item.ID == SelectedItemID;
	});

	return Found ? *Found : FMyItem();
}


void UInventoryManager::AddItem(const int32 InItemID)
{
	Internal_AddItem(InItemID);
	SaveData();
}

void UInventoryManager::AddItems(const TArray<int32>& InItemList)
{
	for (const int32 ItemID : InItemList)
	{
		Internal_AddItem(ItemID);
	}
	
	SaveData();
}

void UInventoryManager::ResetItem()
{
	InventoryItemData.Reset();
	
	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	if (!SaveGameMgr) return;
	
	SaveGameMgr->ClearInvenData();
}

void UInventoryManager::SetSelectedItem(const int32 InItemID)
{
	if (SelectedItemID == InItemID) return;

	SelectedItemID = InItemID;
}

void UInventoryManager::Internal_AddItem(const int32 InItemID)
{
	if (InItemID == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("[InventoryManager] 유효하지 않은 아이템 ID입니다."));
		return;
	}

	UTableManager* TableMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<UTableManager>();
	if (!TableMgr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GachaManager] TableManager를 찾을 수 없습니다."));
		return;
	}
	
	const auto ItemTableData = TableMgr->GetItemTableData(InItemID);
	if (!ItemTableData)
	{
		return;
	}
	
	const auto ItemGradeColor = GTGetMgrImpl(UIManager)->GetItemColor(ItemTableData->ItemGrade);
	
	FMyItem ItemData;
	ItemData.Init(ItemTableData, ItemGradeColor, UniqueInventoryItemID++);
	InventoryItemData.Emplace(ItemData);
	
	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	if (!SaveGameMgr)
	{
		return;
	}
	
	SaveGameMgr->AddInvenData(ItemData);
}

void UInventoryManager::SaveData() const
{
	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	if (!SaveGameMgr) return;
	
	SaveGameMgr->SaveGame(Constant::SaveData);
}

void UInventoryManager::LoadData()
{
	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	if (!SaveGameMgr) return;

	UWLSaveGame* SaveData = SaveGameMgr->GetSaveGame();
	if (!SaveData) return;

	InventoryItemData = SaveData->InvenItemData;
	
	UniqueInventoryItemID = 0;
	for (const auto& Item : InventoryItemData)
	{
		UniqueInventoryItemID = FMath::Max(UniqueInventoryItemID, Item.UniqueID + 1);
	}
}
