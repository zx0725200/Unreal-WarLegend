#include "PopupItemDiscard.h"

#include "Components/VerticalBox.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Slot/SlotFilter.h"
#include "ViewModel/Popup/PopupItemDiscardVM.h"
#include "ViewModel/Slot/SlotFilterVM.h"

void UPopupItemDiscard::Awake()
{
	Super::Awake();
}

void UPopupItemDiscard::OnEnable()
{
	Super::OnEnable();
}

void UPopupItemDiscard::OnDisable()
{
	Super::OnDisable();
	UnbindVM();
}

void UPopupItemDiscard::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
}

void UPopupItemDiscard::BindViewModel()
{
	Super::BindViewModel();

	VM = NewObject<UPopupItemDiscardVM>(this);
	VM->Init();

	BindVM();
	VM->NotifyAll();
}

void UPopupItemDiscard::BindVM()
{
	VALID_RETURN(VM);
	VM->GetOnSlotListChanged().AddUObject(this, &UPopupItemDiscard::HandleSlotListChanged);
}

void UPopupItemDiscard::UnbindVM()
{
	VALID_RETURN(VM);
	VM->GetOnSlotListChanged().RemoveAll(this);
	VM = nullptr;
}

void UPopupItemDiscard::HandleSlotListChanged(const TArray<TObjectPtr<USlotFilterVM>>& InSlotList)
{
	VBox_Filter->ClearChildren();

	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	VALID_RETURN(UIMgr);

	for (USlotFilterVM* SlotVM : InSlotList)
	{
		if (!SlotVM) continue;

		USlotFilter* SlotWidget = UIMgr->CreateSlot<USlotFilter>(TEXT("SlotFilter"), VBox_Filter);
		SlotWidget->SetViewModel(SlotVM);
	}
}
