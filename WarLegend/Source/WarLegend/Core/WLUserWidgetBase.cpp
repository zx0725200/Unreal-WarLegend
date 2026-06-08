#include "WLUserWidgetBase.h"

#include "UMyButton.h"
#include "Blueprint/WidgetTree.h"
#include "Controller/WarLegendPlayerController.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Kismet/GameplayStatics.h"

void UWLUserWidgetBase::Awake()
{
}

void UWLUserWidgetBase::OnEnable()
{
	if (!IsBlockUI())
	{
		return;
	}
	
	SetIsFocusable(true);  
	LockPlayerInput();
}

void UWLUserWidgetBase::OnDisable()
{
	if (!IsBlockUI())
	{
		return;
	}
	
	if (IsEmptyUI())
	{
		UnlockPlayerInput();
		return;
	}
	
	TSharedPtr<SWidget> Prev = CachedFocusedWidget.Pin();
	if (Prev.IsValid())
	{
		FSlateApplication::Get().SetUserFocus(0, Prev, EFocusCause::SetDirectly);
	}
}

void UWLUserWidgetBase::OnDestroy()
{
}

void UWLUserWidgetBase::Update(const float InDeltaTime)
{
}

void UWLUserWidgetBase::SetUIType(EUserWidgetType InType)
{
	WidgetType = InType;
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
	auto* UIMgr = GTUIGetMgrImpl(UIManager);
	VALID_RETURN(UIMgr);
	
	const ESlateVisibility CurrentVisibility = GetVisibility();
	
	// 이미 숨겨진 상태라면 중복 호출 방지
	if (CurrentVisibility == ESlateVisibility::Collapsed || CurrentVisibility == ESlateVisibility::Hidden)
	{
		return;
	}

	UIMgr->RemoveUIStack(RegisteredName);
	
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

void UWLUserWidgetBase::BindViewModel()
{
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
	
	CachedFocusedWidget = FSlateApplication::Get().GetUserFocusedWidget(0);
	
	FInputModeUIOnly UIOnlyGameMode;
	PlayerController->SetInputMode(UIOnlyGameMode);
	
	SetFocus(); 
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

bool UWLUserWidgetBase::IsBlockUI() const
{
	return GetUIType() == EUserWidgetType::Popup || GetUIType() == EUserWidgetType::Screen;
}

bool UWLUserWidgetBase::IsEmptyUI() const
{
	auto* UIMgr = GTUIGetMgrImpl(UIManager);
	if (!UIMgr)
	{
		return true;
	}
	
	return IsBlockUI() && UIMgr->IsEmptyStack();
}
