#include "PopupGachaLog.h"

#include "Components/ScrollBox.h"
#include "Core/UMyButton.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "ETC/Define.h"
#include "Slot/SlotGachaLog.h"
#include "ViewModel/Popup/PopupGachaLogVM.h"

void UPopupGachaLog::Awake()
{
	Super::Awake();
}

void UPopupGachaLog::OnEnable()
{
	Super::OnEnable();
}

void UPopupGachaLog::OnDisable()
{
	Super::OnDisable();
	UnbindVM();
}

void UPopupGachaLog::OnClickEvent(const FName& InChildName)
{
	VALID_RETURN(VM);
	Super::OnClickEvent(InChildName);

	if (InChildName == TEXT("Btn_Clear"))
	{
		VM->ClearAll();
	}
}

void UPopupGachaLog::BindViewModel()
{
	Super::BindViewModel();

	VM = NewObject<UPopupGachaLogVM>(this);
	VM->Init();

	BindVM();
}

void UPopupGachaLog::BindVM()
{
	VALID_RETURN(VM);
	VM->GetOnLogAdded().AddUObject(this, &UPopupGachaLog::HandleLogAdded);
	VM->GetOnLogCleared().AddUObject(this, &UPopupGachaLog::HandleLogCleared);
	
	VM->NotifyAll();
}

void UPopupGachaLog::UnbindVM()
{
	VALID_RETURN(VM);
	
	VM->GetOnLogAdded().RemoveAll(this);
	VM->GetOnLogCleared().RemoveAll(this);
	VM->ClearBinding();
	
	VM = nullptr;
}

void UPopupGachaLog::CreateLogSlot(const FGachaLogData& InData)
{
	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	VALID_RETURN(UIMgr);

	auto* LogSlot = UIMgr->CreateSlot<USlotGachaLog>(TEXT("SlotGachaLog"), SB_Log);
	VALID_RETURN(LogSlot);
	
	LogSlot->Init(InData);
}

void UPopupGachaLog::HandleLogAdded(const FGachaLogData& InData)
{
	CreateLogSlot(InData);
	
	SB_Log->ScrollToEnd();
}

void UPopupGachaLog::HandleLogCleared()
{
	SB_Log->ClearChildren();
}


