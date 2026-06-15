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
	   return Item.UniqueID == SelectedItemID;
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
	EquippedItems.Reset();

	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	VALID_RETURN(SaveGameMgr);

	SaveGameMgr->ClearInvenData();
	SaveGameMgr->SaveGame(Constant::SaveData);
}

void UInventoryManager::SetSelectedItem(const int32 InUniqueID)
{
	if (SelectedItemID == InUniqueID) return;

	SelectedItemID = InUniqueID;
}

void UInventoryManager::EquipItem(const int32 InUniqueID)
{
	const FMyItem* Found = InventoryItemData.FindByPredicate([InUniqueID](const FMyItem& Item)
	{
		return Item.UniqueID == InUniqueID;
	});
	VALID_RETURN(Found);

	// 같은 타입에 장착 중인 아이템이 있으면 교체된다.
	EquippedItems.Add(Found->ItemType, InUniqueID);

	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	VALID_RETURN(SaveGameMgr);

	SaveGameMgr->SetEquippedData(EquippedItems);
	SaveGameMgr->SaveGame(Constant::SaveData);
}

void UInventoryManager::UnequipItem(const EItemType InItemType)
{
	// 해당 타입에 장착된 게 없으면 할 일 없음
	if (EquippedItems.Remove(InItemType) <= 0)
	{
		return;
	}

	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	VALID_RETURN(SaveGameMgr);

	SaveGameMgr->SetEquippedData(EquippedItems);
	SaveGameMgr->SaveGame(Constant::SaveData);
}

const FMyItem* UInventoryManager::FindEquippedItemData(const EItemType InItemType) const
{
	const int32* EquippedUniqueID = EquippedItems.Find(InItemType);
	if (!EquippedUniqueID)
	{
		return nullptr;
	}

	return InventoryItemData.FindByPredicate([EquippedUniqueID](const FMyItem& Item)
	{
		return Item.UniqueID == *EquippedUniqueID;
	});
}

bool UInventoryManager::IsEquippedItem(const int32 InUniqueID) const
{
	for (const auto& Pair : EquippedItems)
	{
		if (Pair.Value == InUniqueID)
		{
			return true;
		}
	}

	return false;
}

FEquipStatTotal UInventoryManager::GetEquippedStatTotal() const
{
	FEquipStatTotal Total;

	for (const auto& Pair : EquippedItems)
	{
		const FMyItem* Equipped = FindEquippedItemData(Pair.Key);
		if (!Equipped)
		{
			continue;
		}

		Total.HP += Equipped->HP;
		Total.ATK += Equipped->ATK;
		Total.DEF += Equipped->DEF;
	}

	return Total;
}

bool UInventoryManager::IsUpgrade(const FMyItem& InItem) const
{
	int32 EquippedTotal = 0;
	if (const FMyItem* Equipped = FindEquippedItemData(InItem.ItemType))
	{
		EquippedTotal = Equipped->GetTotalStat();
	}

	return InItem.GetTotalStat() > EquippedTotal;
}

void UInventoryManager::DiscardItemsByFilter()
{
	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	VALID_RETURN(SaveGameMgr);

	UWLSaveGame* SaveData = SaveGameMgr->GetSaveGame();
	VALID_RETURN(SaveData);

	const TMap<EItemGrade, bool>& DiscardFilter = SaveData->DiscardFilter;

	InventoryItemData.RemoveAll([this, &DiscardFilter](const FMyItem& Item)
	{
		// 장착 중인 아이템은 보호 (선택한 등급이어도 버리지 않는다)
		if (IsEquippedItem(Item.UniqueID))
		{
			return false;
		}

		const bool* bDiscard = DiscardFilter.Find(Item.ItemGrade);
		return bDiscard && *bDiscard;
	});

	SaveGameMgr->SetInvenData(InventoryItemData);
	SaveGameMgr->SaveGame(Constant::SaveData);
}

void UInventoryManager::Internal_AddItem(const int32 InItemID)
{
	if (InItemID == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("[InventoryManager] 유효하지 않은 아이템 ID입니다."));
		return;
	}

	UTableManager* TableMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<UTableManager>();
	VALID_RETURN(TableMgr);

	const auto ItemTableData = TableMgr->GetItemTableData(InItemID);
	VALID_RETURN(ItemTableData);

	const auto ItemGradeColor = GTGetMgrImpl(UIManager)->GetItemColor(ItemTableData->ItemGrade);

	FMyItem ItemData;
	ItemData.Init(ItemTableData, ItemGradeColor, UniqueInventoryItemID++);
	InventoryItemData.Emplace(ItemData);

	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	VALID_RETURN(SaveGameMgr);

	SaveGameMgr->AddInvenData(ItemData);
}

void UInventoryManager::SaveData() const
{
	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	VALID_RETURN(SaveGameMgr);

	SaveGameMgr->SaveGame(Constant::SaveData);
}

void UInventoryManager::LoadData()
{
	USaveGameDataManager* SaveGameMgr = GetLocalPlayer()->GetGameInstance()->GetSubsystem<USaveGameDataManager>();
	VALID_RETURN(SaveGameMgr);

	UWLSaveGame* SaveData = SaveGameMgr->GetSaveGame();
	VALID_RETURN(SaveData);

	InventoryItemData = SaveData->InvenItemData;
	EquippedItems = SaveData->EquippedItemData;

	UniqueInventoryItemID = 0;
	for (const auto& Item : InventoryItemData)
	{
		UniqueInventoryItemID = FMath::Max(UniqueInventoryItemID, Item.UniqueID + 1);
	}

	// 인벤토리에 없는 아이템이 장착돼 있으면 제거 (세이브 꼬임 방지)
	for (auto It = EquippedItems.CreateIterator(); It; ++It)
	{
		const int32 EquippedUniqueID = It.Value();
		const bool bExists = InventoryItemData.ContainsByPredicate([EquippedUniqueID](const FMyItem& Item)
		{
			return Item.UniqueID == EquippedUniqueID;
		});

		if (!bExists)
		{
			It.RemoveCurrent();
		}
	}
}
