#include "WLUserWidgetBase.h"

#include "UMyButton.h"
#include "Blueprint/WidgetTree.h"
#include "Character/WarLegendPlayerController.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Kismet/GameplayStatics.h"

void UWLUserWidgetBase::Awake()
{
}

void UWLUserWidgetBase::OnEnable()
{
	SetIsFocusable(true);
	
	const bool bLockInput = GetUIType() == EUserWidgetType::Popup || GetUIType() == EUserWidgetType::Screen;
	if (bLockInput)
	{
		LockPlayerInput();
	}
}

void UWLUserWidgetBase::OnDisable()
{
	const bool bUnLockInput = GetUIType() == EUserWidgetType::Popup || GetUIType() == EUserWidgetType::Screen;
	if (bUnLockInput)
	{
		UnlockPlayerInput();
	}
}

void UWLUserWidgetBase::OnDestroy()
{
}

void UWLUserWidgetBase::Update(const float InDeltaTime)
{
}

void UWLUserWidgetBase::OnClickEvent(const FName& InChildName)
{
}

void UWLUserWidgetBase::Show(const ESlateVisibility InVisible)
{
	const ESlateVisibility CurrentVisibility = GetVisibility();
	
	// 상태가 동일하면 리턴처리.
	if (CurrentVisibility == InVisible)
	{
		return;
	}
	
	SetVisibility(InVisible);
	
	OnEnable();
}

void UWLUserWidgetBase::Hide(const ESlateVisibility InVisible)
{
	const ESlateVisibility CurrentVisibility = GetVisibility();
	
	// 이미 숨겨진 상태라면 중복 호출 방지
	if (CurrentVisibility == ESlateVisibility::Collapsed || CurrentVisibility == ESlateVisibility::Hidden)
	{
		return;
	}

	SetVisibility(InVisible);
	
	OnDisable();
}

void UWLUserWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UWLUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	TArray<UWidget*> Children;
	WidgetTree->GetAllWidgets(Children);
	
	InitChildWidget(Children);
}

void UWLUserWidgetBase::NativeDestruct()
{
	// 소멸 될 때 호출.
	OnDestroy();
	
	Super::NativeDestruct();
}

FReply UWLUserWidgetBase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		// UIManagerImpl 가져와서 HandleEscClick 호출
		auto* UIMgr = GTUIGetMgrImpl(UIManager);
		if (UIMgr)
		{
			UIMgr->HandleEscClick();
		}
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UWLUserWidgetBase::InitChildWidget(TArray<UWidget*>& Children)
{
	for (const auto Widget : Children)
	{
		if (!Widget)
		{
			continue;
		}
		
		if (const auto MyButton = Cast<UUMyButton>(Widget))
		{
			MyButton->RegActionBase();
			MyButton->OnClickWithNamed.AddDynamic(this, &UWLUserWidgetBase::OnClickEvent);
		}
	}
	
	Awake();
}

void UWLUserWidgetBase::LockPlayerInput()
{
	AWarLegendPlayerController* PlayerController =  Cast<AWarLegendPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PlayerController)
	{
		return;
	}
	
	FInputModeUIOnly UIOnlyGameMode;
	UIOnlyGameMode.SetWidgetToFocus(GetCachedWidget()); // 포커스 잡아서 ESC 받기
	PlayerController->SetInputMode(UIOnlyGameMode);
}

void UWLUserWidgetBase::UnlockPlayerInput() const
{
	AWarLegendPlayerController* PlayerController =  Cast<AWarLegendPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PlayerController)
	{
		return;
	}
	
	FInputModeGameAndUI InputGameMode;
	PlayerController->SetInputMode(InputGameMode);
}
