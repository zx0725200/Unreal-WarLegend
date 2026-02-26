#include "UIFlowPresenter.h"

#include "DataManager/InventoryManager.h"
#include "DataManager/TableManager.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "DataTable/DungeonTableData.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "Hud/HudPlayerState.h"
#include "Popup/PopupDungeonMenu.h"
#include "Screen/ScreenInventory.h"
#include "Screen/ScreenTitle.h"
#include "ViewModel/Popup/PopupDungeonMenuVM.h"
#include "ViewModel/Screen/ScreenInventoryVM.h"
#include "ViewModel/Screen/ScreenTitleVM.h"

void UUIFlowPresenter::OpenScreenTitle()
{
	auto* UIMgr = GTGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	if (const auto ScreenTitle = UIMgr->ShowUI<UScreenTitle>(TEXT("ScreenTitle")))
	{
		UScreenTitleVM* TitleData = NewObject<UScreenTitleVM>(ScreenTitle);
		TitleData->OnConfirmRequested.AddUObject(this, &UUIFlowPresenter::HandleTitleConfirm);
		
		ScreenTitle->SetViewModel(TitleData);
	}
}

void UUIFlowPresenter::OpenScreenInventory()
{
	const auto* GI = GetWorld()->GetGameInstance();
	if (!GI) return;
	
	auto* TableMgr = GI->GetSubsystem<UTableManager>();
	if (!TableMgr) return;
	
	auto* UIMgr = GTGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	auto* InvenMgr = GTGetMgr(UInventoryManager);
	if (!InvenMgr) return;
	
	
	if (auto* ScreenInventory = UIMgr->ShowUI<UScreenInventory>(TEXT("ScreenInventory")))
	{
		UScreenInventoryVM* InventoryData = NewObject<UScreenInventoryVM>(ScreenInventory);
		InventoryData->Init(InvenMgr);
		
		for (uint8 Value = static_cast<uint8>(EItemType::Weapon); Value <= static_cast<uint8>(EItemType::Glove); ++Value)
		{
			const EItemType InItemType = static_cast<EItemType>(Value);
			const FString ItemTypeName = TableMgr->GetItemTypeName(InItemType);
			
			InventoryData->LeftItemTypes.Emplace(InItemType, ItemTypeName);
		}
		
		for (uint8 Value = static_cast<uint8>(EItemType::BossWeapon); Value <= static_cast<uint8>(EItemType::BossArmor); ++Value)
		{
			const EItemType InItemType = static_cast<EItemType>(Value);
			const FString ItemTypeName = TableMgr->GetItemTypeName(InItemType);
			
			InventoryData->RightItemTypes.Emplace(InItemType, ItemTypeName);
		}
		
		ScreenInventory->SetViewModel(InventoryData);
		ScreenInventory->Init();
	}
}

void UUIFlowPresenter::OpenPopupDungeonMenu()
{
	const auto* GI = GetWorld()->GetGameInstance();
	if (!GI) return;

	auto* TableMgr = GI->GetSubsystem<UTableManager>();
	if (!TableMgr) return;

	auto* UIMgr = GTGetMgrImpl(UIManager);
	if (!UIMgr) return;

	const auto DungeonTableDataList = TableMgr->GetDungeonTableData();
	if (DungeonTableDataList.IsEmpty()) return;
	
	if (auto* DungeonPopup = UIMgr->ShowUI<UPopupDungeonMenu>(TEXT("PopupDungeonMenu")))
	{
		TArray<UPopupDungeonMenuVM*> DungeonDataList;
		DungeonDataList.Reserve(DungeonTableDataList.Num());
		
		for (const auto& DungeonData : DungeonTableDataList)
		{
			UPopupDungeonMenuVM* InDungeonData = NewObject<UPopupDungeonMenuVM>(DungeonPopup);
			InDungeonData->ID = DungeonData->DungeonID;
			InDungeonData->Name = DungeonData->DungeonName;
			InDungeonData->MinLevel = DungeonData->MinLevel;
			InDungeonData->MaxLevel = DungeonData->MaxLevel;
		
			InDungeonData->OnConfirmRequested.RemoveAll(this);
			InDungeonData->OnConfirmRequested.AddUObject(this, &UUIFlowPresenter::HandleSlotDungeonMenuClick);
		
			DungeonDataList.Emplace(InDungeonData);
		}
		
		DungeonPopup->SetViewModel(DungeonDataList);
		DungeonPopup->Init();
	}
}

void UUIFlowPresenter::HandleTitleConfirm()
{
	auto* UIMgr = GTGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	UIMgr->ShowUI<UHudPlayerState>(TEXT("HudPlayerState"));
}

void UUIFlowPresenter::HandleSlotDungeonMenuClick(int32 InSlotIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Start Pos Change %d"), InSlotIndex);
}

