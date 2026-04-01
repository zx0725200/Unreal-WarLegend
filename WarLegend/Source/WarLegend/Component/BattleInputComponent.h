// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/BattleInputConfig.h"
#include "BattleInputComponent.generated.h"


struct FGameplayTag;
class UBattleInputConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARLEGEND_API UBattleInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UBattleInputComponent();
	
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(UBattleInputConfig* InBattleInputConfig, const FGameplayTag& InTag, ETriggerEvent InTriggerEvent, UserObject* InContextObj, CallbackFunc InFunc);
};

template <class UserObject, typename CallbackFunc>
void UBattleInputComponent::BindNativeInputAction(UBattleInputConfig* InBattleInputConfig,
	const FGameplayTag& InTag, ETriggerEvent InTriggerEvent, UserObject* InContextObj, CallbackFunc InFunc)
{
	if (auto* FoundAction = InBattleInputConfig->GetBattleInputAction(InTag))
	{
		BindAction(FoundAction, InTriggerEvent, InContextObj, InFunc);
	}
}
