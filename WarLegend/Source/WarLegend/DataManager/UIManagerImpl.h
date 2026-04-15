// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SlateWrapperTypes.h"
#include "Interface/IViewModelInterface.h"
#include "UObject/Object.h"
#include "UIManagerImpl.generated.h"

enum class EItemGrade : uint8;
class UPanelWidget;
class UUIManagerConfig;
class UWLUserWidgetBase;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WARLEGEND_API UUIManagerImpl : public UObject
{
	GENERATED_BODY()
	
public:
	UUIManagerImpl();
	
	virtual void Initialize();
	virtual void Deinitialize();

public:
	UWLUserWidgetBase* ShowUI(const FName& UIName, ESlateVisibility Visible = ESlateVisibility::Visible);
	void HideUI(const FName& UIName, ESlateVisibility Visible = ESlateVisibility::Collapsed);
	
	template <class TRetType>
	TRetType* ShowUI(const FName& UIName, ESlateVisibility Visible);
	
	template <class TRetType>
	TRetType* CreateSlot(const FName& InName, UPanelWidget* InParent);
	
public:
	void HandleEscClick();

	FLinearColor GetItemColor(const EItemGrade InItemGrade) const;
	
private:
	void HideUIBase(const FName& InName, ESlateVisibility InVisibility = ESlateVisibility::Collapsed);
	void AttachWidget(UUserWidget* InWidget, UPanelWidget* InParent);
	
	UWLUserWidgetBase* ShowUIBase(const FName& InName, ESlateVisibility InVisibility = ESlateVisibility::Visible);
	UWLUserWidgetBase* CreateSlotBase(const FName& InName, UPanelWidget* InParent);
	UWLUserWidgetBase* CreateMyWidget(const FName& InName);

private:
	UPROPERTY(Transient)
	TMap<FName, TObjectPtr<UWLUserWidgetBase>> WidgetCache;
	
	UPROPERTY()
	TObjectPtr<UUIManagerConfig> ConfigAsset = nullptr;
	
	UPROPERTY()
	TArray<TObjectPtr<UWLUserWidgetBase>> UIStack;
};

template <typename TRetType>
TRetType* UUIManagerImpl::ShowUI(const FName& UIName, ESlateVisibility Visible = ESlateVisibility::Visible)
{
	if (TRetType* Widget = Cast<TRetType>(ShowUIBase(UIName, Visible)))
	{
		// 인터페이스로 캐스팅 시도
		if (auto* VMWidget = Cast<IViewModelInterface>(Widget))
		{
			VMWidget->BindViewModel();
		}
		
		return Widget;
	}
	
	return nullptr;
}

template <typename TRetType>
TRetType* UUIManagerImpl::CreateSlot(const FName& InName, UPanelWidget* InParent)
{
	return Cast<TRetType>(CreateSlotBase(InName, InParent));
}
