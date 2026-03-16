#include "PopupDungeonMenu.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Slot/SlotDungeonMenu.h"

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
}

void UPopupDungeonMenu::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Next"))
	{
		OnClickedNext();
	}
	else if (InChildName == TEXT("Btn_Prev"))
	{
		OnClickedPrev();
	}
}

void UPopupDungeonMenu::Init()
{
	CurrentPageIndex = 1;
	
	InitSlotPool();
	RefreshPage();
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
	if (!UIMgr) return;
	
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

void UPopupDungeonMenu::RefreshPage()
{
	if (!Vertical_DungeonMenu || PooledSlots.Num() <= 0)
	{
		return;
	}
	
	constexpr int32 PageSize = 5;
	const int32 StartIndex = (CurrentPageIndex-1) * PageSize;

	for (int32 LocalIndex = 0; LocalIndex < PooledSlots.Num(); ++LocalIndex)
	{
		USlotDungeonMenu* DungeonMenu = PooledSlots[LocalIndex];
		if (!DungeonMenu)
		{
			continue;
		}

		const int32 DataIndex = StartIndex + LocalIndex;

		if (VM.IsValidIndex(DataIndex) && VM[DataIndex])
		{
			DungeonMenu->SetData(VM[DataIndex]);
			DungeonMenu->Show();
		}
	}
	
	RefreshPageText();
}

void UPopupDungeonMenu::RefreshPageText() const
{
	const int32 MaxPageIndex = GetMaxPageIndex();
	const FString PageText = FString::Printf(TEXT("%d/%d"), CurrentPageIndex, MaxPageIndex);
	
	Txt_Page->SetText(FText::FromString(PageText));
}

int32 UPopupDungeonMenu::GetMaxPageIndex() const
{
	constexpr int32 PageSize = 5;
	if (VM.Num() <= 0)
	{
		return 0;
	}

	return FMath::DivideAndRoundUp(VM.Num(), PageSize);
}

void UPopupDungeonMenu::OnClickedNext()
{
	const int32 MaxPageIndex = GetMaxPageIndex();
	if (CurrentPageIndex >= MaxPageIndex)
	{
		return;
	}

	++CurrentPageIndex;
	RefreshPage();
}

void UPopupDungeonMenu::OnClickedPrev()
{
	if (CurrentPageIndex <= 1)
	{
		return;
	}

	--CurrentPageIndex;
	RefreshPage();
}
