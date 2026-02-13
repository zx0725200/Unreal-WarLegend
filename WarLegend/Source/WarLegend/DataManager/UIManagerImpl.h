// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SlateWrapperTypes.h"
#include "UObject/Object.h"
#include "UIManagerImpl.generated.h"

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
	
	UWLUserWidgetBase* ShowUI(const FName& InName, ESlateVisibility InVisibility = ESlateVisibility::SelfHitTestInvisible);
	void HideUI(const FName& InName, ESlateVisibility InVisibility = ESlateVisibility::Collapsed);
	
private:
	UWLUserWidgetBase* CreateMyWidget(const FName& InName);

private:
	UPROPERTY(Transient)
	TMap<FName, TObjectPtr<UWLUserWidgetBase>> WidgetCache;
	
	UPROPERTY()
	TObjectPtr<UUIManagerConfig> ConfigAsset = nullptr;
};
