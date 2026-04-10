// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "HeroBattleInputConfig.generated.h"

class UInputMappingContext;
class UInputAction;
struct FGameplayTag;

USTRUCT(BlueprintType)
struct FBattleInputStruct
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories = "Battle"))
	FGameplayTag BattleTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> BattleAction;
};

UCLASS()
class WARLEGEND_API UHeroBattleInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UInputAction* GetBattleInputAction(const FGameplayTag& InInputTag);
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> MappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "BattleAction"))
	TArray<FBattleInputStruct> BattleInputActions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "BattleAction"))
	TArray<FBattleInputStruct> AbilityInputActions;
};
