#include "UIFlowPresenter.h"

#include "DungeonPresenter.h"
#include "GachaPresenter.h"
#include "InventoryPresenter.h"
#include "DataManager/InventoryManager.h"
#include "DataManager/TableManager.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "DataManager/GachaManager.h"
#include "DataManager/SaveGameDataManager.h"
#include "DataManager/DungeonManager.h"
#include "ETC/Define.h"
#include "Hud/HudPlayerState.h"
#include "Screen/ScreenTitle.h"
#include "ViewModel/Screen/ScreenTitleVM.h"

void UUIFlowPresenter::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// DungeonPresenter = NewObject<UDungeonPresenter>(this);
	// InventoryPresenter = NewObject<UInventoryPresenter>(this);
	// GachaPresenter = NewObject<UGachaPresenter>(this);
}

void UUIFlowPresenter::PlayerControllerChanged(APlayerController* NewPlayerController)
{
	Super::PlayerControllerChanged(NewPlayerController);

	const auto* GI      = GetLocalPlayer()->GetGameInstance();
	auto* UIMgr= GTGetMgrImpl(UIManager);
	auto* TableMgr = GI->GetSubsystem<UTableManager>();
	auto* DungeonMgr = GI->GetSubsystem<UDungeonManager>();
	auto* InvenMgr = GTGetMgr(UInventoryManager);
	
	DungeonPresenter->Init(UIMgr, TableMgr, DungeonMgr);
	GachaPresenter->Init(UIMgr);
	InventoryPresenter->Init(UIMgr, InvenMgr, TableMgr);
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

void UUIFlowPresenter::OpenPopupGachaLog() const
{
	if (!GachaPresenter) return;
	
	GachaPresenter->OpenPopupGachaLog();
}

void UUIFlowPresenter::GotoCity() const
{
	
}
