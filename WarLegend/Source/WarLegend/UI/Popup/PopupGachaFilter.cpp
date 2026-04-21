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
	VM = nullptr;
}

void UPopupGachaFilter::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
}

void UPopupGachaFilter::BindViewModel()
{
	Super::BindViewModel();
	
	auto* GachaFilterVM = NewObject<UPopupGachaFilterVM>(this);
	GachaFilterVM->Init();
	
	SetViewModel(GachaFilterVM);
	
	RefreshSlots();
}

void UPopupGachaFilter::SetViewModel(UPopupGachaFilterVM* InVM)
{
	VM = InVM;
}

void UPopupGachaFilter::RefreshSlots()
{
	VALID_RETURN(VM);
	
	VBox_Filter->ClearChildren();

	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	VALID_RETURN(UIMgr);
	
	const auto SlotList = VM->GetSlotVMList();
	if (SlotList.IsEmpty()) return;
	
	for (USlotFilterVM* SlotVM : SlotList)
	{
		if (!SlotVM) continue;

		USlotFilter* SlotWidget = UIMgr->CreateSlot<USlotFilter>(TEXT("SlotFilter"), VBox_Filter);
		SlotWidget->SetViewModel(SlotVM);
	}
}
