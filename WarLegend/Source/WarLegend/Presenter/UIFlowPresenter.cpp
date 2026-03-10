#include "UIFlowPresenter.h"

#include "DungeonPresenter.h"
#include "GachaPresenter.h"
#include "InventoryPresenter.h"
#include "DataManager/InventoryManager.h"
#include "DataManager/TableManager.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "DataManager/GachaManager.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "Hud/HudPlayerState.h"
#include "Screen/ScreenInventory.h"
#include "Screen/ScreenTitle.h"
#include "ViewModel/Screen/ScreenInventoryVM.h"
#include "ViewModel/Screen/ScreenTitleVM.h"

void UUIFlowPresenter::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	DungeonPresenter = NewObject<UDungeonPresenter>(this);
	InventoryPresenter = NewObject<UInventoryPresenter>(this);
	GachaPresenter = NewObject<UGachaPresenter>(this);
}

void UUIFlowPresenter::PlayerControllerChanged(APlayerController* NewPlayerController)
{
	Super::PlayerControllerChanged(NewPlayerController);

	const auto* GI      = GetLocalPlayer()->GetGameInstance();
	auto* UIMgr= GTGetMgrImpl(UIManager);
	auto* TableMgr = GI->GetSubsystem<UTableManager>();
	auto* GachaMgr = GI->GetSubsystem<UGachaManager>();
	auto* InvenMgr      = GTGetMgr(UInventoryManager);
	
	DungeonPresenter->Init(UIMgr, TableMgr);
	GachaPresenter->Init(UIMgr, GachaMgr, InvenMgr);
}

void UUIFlowPresenter::HandleEscClick()
{
	auto* UIMgr = GTGetMgrImpl(UIManager);
	if (!UIMgr) return;
	
	UIMgr->HandleEscClick();
}

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

void UUIFlowPresenter::OpenPopupDungeonMenu() const
{
	if (!DungeonPresenter) return;
	
	DungeonPresenter->OpenPopupDungeonMenu();
}

void UUIFlowPresenter::OpenPopupGacha() const
{
	if (!GachaPresenter) return;
	
	GachaPresenter->OpenPopupGacha();
}

void UUIFlowPresenter::OpenPopupGachaFilter() const
{
	if (!GachaPresenter) return;
	
	GachaPresenter->OpenPopupGachaFilter();
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

