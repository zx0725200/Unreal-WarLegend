#include "PopupDungeonMenu.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Popup/PopupDungeonMenuVM.h"
#include "UI/Slot/SlotDungeonMenu.h"

void UPopupDungeonMenu::Awake()
{
	Super::Awake();
}

void UPopupDungeonMenu::OnEnable()
{
	Super::OnEnable();
}

void UPopupDungeonMenu::OnDisable()
{
	Super::OnDisable();
	UnbindVM();
}

void UPopupDungeonMenu::OnClickEvent(const FName& InChildName)
{
	VALID_RETURN(VM);
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Next"))
	{
		VM->OnNextPage();
	}
	else if (InChildName == TEXT("Btn_Prev"))
	{
		VM->OnPrevPage();
	}
}

void UPopupDungeonMenu::InitSlotPool()
{
	if (PooledSlots.Num() > 0)
	{
		return;
	}
	
	Vertical_DungeonMenu->ClearChildren();

	constexpr int32 PageSize = 5;
	PooledSlots.Empty();
	PooledSlots.Reserve(PageSize);

	const auto UIMgr = GTUIGetMgrImpl(UIManager);
	VALID_RETURN(UIMgr);
	
	for (int32 i = 0; i < PageSize; ++i)
	{
		USlotDungeonMenu* DungeonMenu = UIMgr->CreateSlot<USlotDungeonMenu>(TEXT("SlotDungeonMenu"),Vertical_DungeonMenu);
		if (!DungeonMenu)
		{
			continue;
		}
		
		DungeonMenu->Hide();
		PooledSlots.Add(DungeonMenu);
	}
}

void UPopupDungeonMenu::BindVM()
{
	VALID_RETURN(VM);
	VM->GetOnPageChanged().AddUObject(this, &UPopupDungeonMenu::OnPageChanged);
}

void UPopupDungeonMenu::UnbindVM()
{
	VALID_RETURN(VM);
	VM->GetOnPageChanged().RemoveAll(this);
	VM = nullptr;
}

void UPopupDungeonMenu::OnPageChanged(const TArray<USlotDungeonVM*>& InSlotList, const int32 InCurrentPage, const int32 InMaxPage)
{
	for (int32 i = 0; i < PooledSlots.Num(); ++i)
	{
		USlotDungeonMenu* DungeonMenu = PooledSlots[i];
		if (!DungeonMenu)
		{
			continue;
		}

		if (InSlotList.IsValidIndex(i) && InSlotList[i])
		{
			DungeonMenu->SetData(InSlotList[i]);
			DungeonMenu->Show();
		}
		else
		{
			DungeonMenu->Hide();
		}
	}
	
	Txt_Page->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), InCurrentPage, InMaxPage)));
}

void UPopupDungeonMenu::BindViewModel()
{
	Super::BindViewModel();
	
	VM = NewObject<UPopupDungeonMenuVM>(this);
	VM->Init();
	
	InitSlotPool();
	
	BindVM();
	VM->NotifyAll();   // 처음 호출
}
