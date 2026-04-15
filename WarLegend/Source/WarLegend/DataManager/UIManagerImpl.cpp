// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerImpl.h"

#include "Components/CanvasPanel.h"
#include "Core/SlotWidgetBase.h"
#include "Core/WLUserWidgetBase.h"
#include "DataAsset/UIManagerConfig.h"

UUIManagerImpl::UUIManagerImpl()
{
	static ConstructorHelpers::FObjectFinder<UUIManagerConfig> Finder(TEXT("/Script/WarLegend.UIManagerConfig'/Game/UMG/Etc/UIManagerConfig.UIManagerConfig'"));
	ConfigAsset = Finder.Object;
}

void UUIManagerImpl::Initialize()
{
	
}

void UUIManagerImpl::Deinitialize()
{
	for (const auto& Widget : WidgetCache)
	{
		if (UWLUserWidgetBase* WidgetBase = Widget.Value.Get())
		{
			WidgetBase->RemoveFromParent();
		}
	}
	
	WidgetCache.Empty();
}

UWLUserWidgetBase* UUIManagerImpl::ShowUI(const FName& UIName, ESlateVisibility Visible)
{
	UWLUserWidgetBase* Widget = ShowUIBase(UIName, Visible);
	if (!Widget)
	{
		return nullptr;
	}

	if (auto* VMWidget = Cast<IViewModelInterface>(Widget))
	{
		VMWidget->BindViewModel();
	}
	
	return Widget;
}

void UUIManagerImpl::HideUI(const FName& UIName, ESlateVisibility Visible)
{
	HideUIBase(UIName, Visible);
}

UWLUserWidgetBase* UUIManagerImpl::ShowUIBase(const FName& InName, ESlateVisibility InVisibility)
{
	if (const auto MyWidget = CreateMyWidget(InName))
	{
		if (!MyWidget->IsInViewport())
		{
			MyWidget->AddToViewport();
		}
		
		const bool bPlusStack = MyWidget->GetUIType() == EUserWidgetType::Popup || MyWidget->GetUIType() == EUserWidgetType::Screen;
		if (bPlusStack)
		{
			UIStack.Remove(MyWidget);
			UIStack.Add(MyWidget);
		}
		
		MyWidget->Show(InVisibility);
		return MyWidget;
	}
	
	return nullptr;
}

void UUIManagerImpl::HandleEscClick()
{
	if (UIStack.IsEmpty()) return;

	UWLUserWidgetBase* TopWidget = UIStack.Last();
	if (!TopWidget) return;

	UIStack.Pop();
	TopWidget->Hide();
}

FLinearColor UUIManagerImpl::GetItemColor(const EItemGrade InItemGrade) const
{
	return *ConfigAsset->ItemColor.Find(InItemGrade);
}

void UUIManagerImpl::HideUIBase(const FName& InName, ESlateVisibility InVisibility)
{
	if (const TObjectPtr<UWLUserWidgetBase>* FoundWidget = WidgetCache.Find(InName))
	{
		if (UWLUserWidgetBase* FindWidget = FoundWidget->Get())
		{
			UIStack.Remove(FindWidget);
			
			FindWidget->Hide(InVisibility);
		}
	}
}

UWLUserWidgetBase* UUIManagerImpl::CreateSlotBase(const FName& InName, UPanelWidget* InParent)
{
	if (UWLUserWidgetBase* MyWidget = CreateMyWidget(InName))
	{
		AttachWidget(MyWidget, InParent);
		MyWidget->Show(ESlateVisibility::SelfHitTestInvisible);
		return MyWidget;
	}
	
	return nullptr;
}

void UUIManagerImpl::AttachWidget(UUserWidget* InWidget, UPanelWidget* InParent)
{
	if (!InWidget) return;
	
	if (!InParent)
	{
		if (!InWidget->IsInViewport())
		{
			InWidget->AddToViewport();
		}
		return;
	}
	
	InParent->AddChild(InWidget);
}

UWLUserWidgetBase* UUIManagerImpl::CreateMyWidget(const FName& InName)
{
	if (!ConfigAsset)
	{
		return nullptr;
	}

	TSubclassOf<UWLUserWidgetBase>* BaseClass = ConfigAsset->WidgetClasses.Find(InName);
	if (!BaseClass || !*BaseClass)
	{
		return nullptr;
	}

	const bool bShouldCache = !(*BaseClass)->IsChildOf(USlotWidgetBase::StaticClass());

	if (bShouldCache)
	{
		if (TObjectPtr<UWLUserWidgetBase>* Found = WidgetCache.Find(InName))
		{
			return Found->Get();
		}
	}

	UWLUserWidgetBase* MyWidget = CreateWidget<UWLUserWidgetBase>(GetWorld(), *BaseClass);
	if (!MyWidget)
	{
		return nullptr;
	}

	if (bShouldCache)
	{
		WidgetCache.Add(InName, MyWidget);
	}

	return MyWidget;
}
