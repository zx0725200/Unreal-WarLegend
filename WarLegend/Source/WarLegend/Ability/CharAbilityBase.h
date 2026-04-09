// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CharAbilityBase.generated.h"

class UCharAbilitySystemComponent;
class UCharCombatComponent;

UENUM(BlueprintType)
enum class ECharAbilityApplyType : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class WARLEGEND_API UCharAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	// 어빌리티 등록되고 콜백 실행.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	// 블루프린트 호출 용
	UFUNCTION(BlueprintPure, Category = "Char|Ability")
	UCharCombatComponent* GetPawnCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Char|Ability")
	UCharAbilitySystemComponent* GetCharAbilityComponentFromActorInfo() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "CharAbility")
	ECharAbilityApplyType AbilityApplyType = ECharAbilityApplyType::OnTriggered;
};
