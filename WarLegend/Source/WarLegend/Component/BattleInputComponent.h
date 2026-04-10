// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/HeroBattleInputConfig.h"
#include "BattleInputComponent.generated.h"


struct FGameplayTag;
class UHeroBattleInputConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARLEGEND_API UBattleInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UBattleInputComponent();
	
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(UHeroBattleInputConfig* InBattleInputConfig, const FGameplayTag& InTag, ETriggerEvent InTriggerEvent, UserObject* InContextObj, CallbackFunc InFunc);

	template<class UserObject,typename CallbackFunc>
	void BindAbilityInputAction(const UHeroBattleInputConfig* InBattleInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UBattleInputComponent::BindNativeInputAction(UHeroBattleInputConfig* InBattleInputConfig,
	const FGameplayTag& InTag, ETriggerEvent InTriggerEvent, UserObject* InContextObj, CallbackFunc InFunc)
{
	if (auto* FoundAction = InBattleInputConfig->GetBattleInputAction(InTag))
	{
		BindAction(FoundAction, InTriggerEvent, InContextObj, InFunc);
	}
}

template <class UserObject, typename CallbackFunc>
void UBattleInputComponent::BindAbilityInputAction(const UHeroBattleInputConfig* InBattleInputConfig,
	UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	for (const FBattleInputStruct& AbilityInputActionConfig : InBattleInputConfig->AbilityInputActions)
	{
		if(!AbilityInputActionConfig.BattleTag.IsValid() || !AbilityInputActionConfig.BattleAction) continue;

		BindAction(AbilityInputActionConfig.BattleAction,ETriggerEvent::Started,ContextObject, InputPressedFunc,AbilityInputActionConfig.BattleTag);
		BindAction(AbilityInputActionConfig.BattleAction,ETriggerEvent::Completed,ContextObject, InputReleasedFunc,AbilityInputActionConfig.BattleTag);
	}
}
