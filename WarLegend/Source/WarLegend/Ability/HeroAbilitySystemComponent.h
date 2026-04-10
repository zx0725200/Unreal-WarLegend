// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HeroAbilitySystemComponent.generated.h"

struct FWarriorHeroAbilitySet;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UHeroAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// 캐릭터 컨트롤러에서 Bind 호출용.
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability", meta = (ApplyLevel = "1"))
	void GiveWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& InWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutAbilityHandles);
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void RemoveWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InRemoveHandle);
};
