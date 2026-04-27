// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonAbilityBase.h"
#include "HeroAbility.generated.h"

enum class EConfirmType : uint8;
class AWarLegendPlayerController;
class AWarLegendCharacter;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UHeroAbility : public UCommonAbilityBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	AWarLegendCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	AWarLegendPlayerController* GetHeroControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> InEffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount);

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EConfirmType& OutSuccessType);
	
private:
	TWeakObjectPtr<AWarLegendCharacter> HeroCharacter;
	TWeakObjectPtr<AWarLegendPlayerController> HeroController;
};
