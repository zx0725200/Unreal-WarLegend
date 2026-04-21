#include "PopupGachaFilter.h"

#include "Components/VerticalBox.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Slot/SlotFilter.h"
#include "ViewModel/Popup/PopupGachaFilterVM.h"
#include "ViewModel/Slot/SlotFilterVM.h"

void UPopupGachaFilter::Awake()
{
	Super::Awake();
}

void UPopupGachaFilter::OnEnable()
{
	Super::OnEnable();
}

void UPopupGachaFilter::OnDisable()
{
	Super::OnDisable();
	UnbindVM();
}

void UPopupGachaFilter::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
}

void UPopupGachaFilter::BindViewModel()
{
	Super::BindViewModel();

	VM = NewObject<UPopupGachaFilterVM>(this);
	VM->Init();

	BindVM();
	VM->NotifyAll();
}

void UPopupGachaFilter::BindVM()
{
	VALID_RETURN(VM);
	VM->GetOnSlotListChanged().AddUObject(this, &UPopupGachaFilter::HandleSlotListChanged);
}

void UPopupGachaFilter::UnbindVM()
{
	VALID_RETURN(VM);
	VM->GetOnSlotListChanged().RemoveAll(this);
	VM = nullptr;
}

void UPopupGachaFilter::HandleSlotListChanged(const TArray<TObjectPtr<USlotFilterVM>>& InSlotList)
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

