// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Base/EnemyAbility.h"
#include "GA_BossAttack.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UGA_BossAttack : public UEnemyAbility
{
	GENERATED_BODY()
	
public:
	UGA_BossAttack();
	
protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
private:
	UFUNCTION() 
	void OnMontageCompleted();
	
	UFUNCTION() 
	void OnMontageInterrupted();
	
	UFUNCTION() 
	void OnHitEventReceived(FGameplayEventData Payload);

	FGameplayEffectSpecHandle MakeDamageSpec(const FHitResult& Hit) const;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	FGameplayTag HitEventTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TMap<FGameplayTag, float> SetByCallerMagnitudes ;
};
