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
	Super::OnClickEvent(InChildName);

	if (InChildName == TEXT("Btn_Clear"))
	{
		OnClickedClear();
	}
}

void UPopupGachaLog::BindViewModel()
{
	Super::BindViewModel();

	VM = NewObject<UPopupGachaLogVM>(this);
	VM->Init();

	BindVM();
	RebuildLogs();
}

void UPopupGachaLog::BindVM()
{
	VALID_RETURN(VM);
	VM->GetOnLogAdded().AddUObject(this, &UPopupGachaLog::HandleLogAdded);
	VM->GetOnLogCleared().AddUObject(this, &UPopupGachaLog::HandleLogCleared);
}

void UPopupGachaLog::UnbindVM()
{
	if (VM)
	{
		VM->GetOnLogAdded().RemoveAll(this);
		VM->GetOnLogCleared().RemoveAll(this);
		VM->ClearBinding();
	}
	VM = nullptr;
}

void UPopupGachaLog::RebuildLogs()
{
	VALID_RETURN(VM, SB_Log);

	SB_Log->ClearChildren();

	for (const FGachaLogData& Data : VM->GetLogList())
	{
		CreateLogSlot(Data);
	}

	SB_Log->ScrollToEnd();
}

void UPopupGachaLog::CreateLogSlot(const FGachaLogData& InData)
{
	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	if (!UIMgr) return;

	auto* LogSlot = UIMgr->CreateSlot<USlotGachaLog>(TEXT("SlotGachaLog"), SB_Log);
	if (LogSlot)
	{
		LogSlot->Init(InData);
	}
}

void UPopupGachaLog::HandleLogAdded(const FGachaLogData& InData)
{
	CreateLogSlot(InData);
	if (SB_Log)
	{
		SB_Log->ScrollToEnd();
	}
}

void UPopupGachaLog::HandleLogCleared()
{
	if (SB_Log)
	{
		SB_Log->ClearChildren();
	}
}

void UPopupGachaLog::OnClickedClear()
{
	if (!VM)
	{
		return;
	}

	VM->ClearAll();
}

