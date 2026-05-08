// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Base/HeroAbility.h"
#include "GA_SpawnWeapon.generated.h"

class AHeroWeaponBase;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UGA_SpawnWeapon : public UHeroAbility
{
	GENERATED_BODY()
	
public:
	UGA_SpawnWeapon();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	void AttachToHero(USkeletalMeshComponent* InHero, AHeroWeaponBase* InWeapon) const;
	
	AHeroWeaponBase* SpawnWeaponActor();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AHeroWeaponBase> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName SocketNameToAttach;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (Categories = "Weapon"))
	FGameplayTag WeaponTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool bRegister = true;
};
