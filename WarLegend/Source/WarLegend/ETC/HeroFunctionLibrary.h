// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HeroFunctionLibrary.generated.h"

class UPawnCombatComponentBase;
class UHeroCombatComponent;
struct FGameplayTag;
class UHeroAbilitySystemComponent;
/**
 * 
 */
UENUM()
enum class EHeroConfirmType : uint8
{
	Yes,
	No
};

UCLASS()
class WARLEGEND_API UHeroFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UPawnCombatComponentBase* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Hero|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutConfirmType"))
	static UPawnCombatComponentBase* BP_GetPawnCombatComponentFromActor(AActor* InActor, EHeroConfirmType& OutConfirmType);
	
	UFUNCTION()
	static UPawnCombatComponentBase* GetPawnCombatComponentFromActor(AActor* InActor);
};
