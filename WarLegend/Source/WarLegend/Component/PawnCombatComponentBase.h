// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PawnExtensionComponentBase.h"
#include "PawnCombatComponentBase.generated.h"


struct FGameplayTag;
class AHeroWeaponBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARLEGEND_API UPawnCombatComponentBase : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	virtual void OnHitTargetActor(AActor* HitActor, const FHitResult& InHitResult);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);
	
	void ToggleWeaponCollision(const ECollisionEnabled::Type InCollisionType);
	
	UFUNCTION(BlueprintCallable, Category = "Hero|Combat")
	AHeroWeaponBase* GetCarriedWeaponByTag(const FGameplayTag InWeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Hero|Combat")
	AHeroWeaponBase* GetCurrentEquippedWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category = "Hero|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTag, AHeroWeaponBase* InWeapon, const bool bRegister = false);

private:
	FGameplayTag CurrentEquippedWeaponTag;
	
protected:
	UPROPERTY()
	TArray<TObjectPtr<AActor>> OverlappedActorList;

private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<AHeroWeaponBase>> CharacterWeaponMap;
	
};
