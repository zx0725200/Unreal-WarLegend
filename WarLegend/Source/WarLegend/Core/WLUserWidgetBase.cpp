#include "WLUserWidgetBase.h"

void UWLUserWidgetBase::Awake()
{
}

void UWLUserWidgetBase::OnEnable()
{
}

void UWLUserWidgetBase::OnDisable()
{
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
	
	if (InVisible == ESlateVisibility::Collapsed || InVisible == ESlateVisibility::Hidden)
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
}

void UWLUserWidgetBase::NativeDestruct()
{
	// 소멸 될 때 호출.
	OnDestroy();
	
	Super::NativeDestruct();
}
