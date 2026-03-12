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
#include "ETC/Define.h"
#include "Hud/HudPlayerState.h"
#include "Screen/ScreenTitle.h"
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
	auto* SaveGameMgr = GI->GetSubsystem<USaveGameDataManager>();
	auto* InvenMgr = GTGetMgr(UInventoryManager);
	
	DungeonPresenter->Init(UIMgr, TableMgr);
	GachaPresenter->Init(UIMgr, GachaMgr, InvenMgr, SaveGameMgr);
	InventoryPresenter->Init(UIMgr, InvenMgr, TableMgr);
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
	if (!InventoryPresenter) return;
	
	InventoryPresenter->OpenScreenInventory();
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

