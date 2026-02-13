// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UMyButton.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonActionWithNameEvent,const FName&, ChildName);

UCLASS()
class WARLEGEND_API UUMyButton : public UButton
{
	GENERATED_BODY()
	
	UUMyButton(const FObjectInitializer& ObjectInitializer);
	
public:
	FOnButtonActionWithNameEvent OnClickWithNamed;
	FOnButtonActionWithNameEvent OnPressedWithNamed;
	FOnButtonActionWithNameEvent OnReleaseWithNamed;
	FOnButtonActionWithNameEvent OnHoverWithNamed;
	FOnButtonActionWithNameEvent OnUnhoverWithNamed;
	
	void RegActionBase();

	UFUNCTION()
	void OnClickBase();
};
