// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerImpl.h"

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

UWLUserWidgetBase* UUIManagerImpl::ShowUI(const FName& InName, ESlateVisibility InVisibility)
{
	if (const auto MyWidget = CreateMyWidget(InName))
	{
		if (!MyWidget->IsInViewport())
		{
			MyWidget->AddToViewport();
		}
		
		MyWidget->Show(InVisibility);
		return MyWidget;
	}
	
	return nullptr;
}

void UUIManagerImpl::HideUI(const FName& InName, ESlateVisibility InVisibility)
{
	if (const TObjectPtr<UWLUserWidgetBase>* FoundWidget = WidgetCache.Find(InName))
	{
		if (UWLUserWidgetBase* W = FoundWidget->Get())
		{
			W->Hide(InVisibility);
		}
	}
}

UWLUserWidgetBase* UUIManagerImpl::CreateMyWidget(const FName& InName)
{
	if (!ConfigAsset)
	{
		return nullptr;
	}
	
	if (TObjectPtr<UWLUserWidgetBase>* FoundWidget = WidgetCache.Find(InName))
	{
		return FoundWidget->Get();
	}

	TSubclassOf<UWLUserWidgetBase>* BaseClass = ConfigAsset->WidgetClasses.Find(InName);
	if (!BaseClass || !*BaseClass)
	{
		return nullptr;
	}
	
	UWLUserWidgetBase* MyWidget = CreateWidget<UWLUserWidgetBase>(GetWorld(), *BaseClass);
	if (!MyWidget)
	{
		return nullptr;
	}

	WidgetCache.Add(InName, MyWidget);
	return MyWidget;
}