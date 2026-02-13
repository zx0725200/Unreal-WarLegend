#include "Core/HudWidgetBase.h"

void UHudWidgetBase::Awake()
{
	Super::Awake();
}

void UHudWidgetBase::OnEnable()
{
	Super::OnEnable();
}

void UHudWidgetBase::OnDisable()
{
	Super::OnDisable();
}

void UHudWidgetBase::OnDestroy()
{
	Super::OnDestroy();
}

void UHudWidgetBase::Update(const float InDeltaTime)
{
	Super::Update(InDeltaTime);
}

void UHudWidgetBase::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
}
