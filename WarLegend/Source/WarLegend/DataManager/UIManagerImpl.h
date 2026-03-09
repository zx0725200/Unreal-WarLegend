// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SlateWrapperTypes.h"
#include "UObject/Object.h"
#include "UIManagerImpl.generated.h"

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
	template <class TRetType>
	TRetType* ShowUI(const FName& UIName, ESlateVisibility Visible);
	
	template <class TRetType>
	TRetType* CreateSlot(const FName& InName, UPanelWidget* InParent);
	
	void HandleEscClick();

private:
	void HideUIBase(const FName& InName, ESlateVisibility InVisibility = ESlateVisibility::Collapsed);
	void AttachWidget(UUserWidget* InWidget, UPanelWidget* InParent);
	
	UWLUserWidgetBase* ShowUIBase(const FName& InName, ESlateVisibility InVisibility = ESlateVisibility::SelfHitTestInvisible);
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
	return Cast<TRetType>(ShowUIBase(UIName, Visible));
}

template <typename TRetType>
TRetType* UUIManagerImpl::CreateSlot(const FName& InName, UPanelWidget* InParent)
{
	return Cast<TRetType>(CreateSlotBase(InName, InParent));
}