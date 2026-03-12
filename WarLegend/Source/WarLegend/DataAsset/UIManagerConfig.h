// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIManagerConfig.generated.h"

enum class EItemGrade : uint8;
class UWLUserWidgetBase;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UUIManagerConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="UI")
	TMap<FName, TSubclassOf<UWLUserWidgetBase>> WidgetClasses;
	
	UPROPERTY(EditAnywhere, Category="ItemColor")
	TMap<EItemGrade, FLinearColor> ItemColor;
};
