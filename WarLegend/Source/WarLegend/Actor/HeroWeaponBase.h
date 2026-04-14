// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "ETC/Struct.h"
#include "GameFramework/Actor.h"
#include "HeroWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class WARLEGEND_API AHeroWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AHeroWeaponBase();
	
	UFUNCTION(BlueprintCallable)
	void SetAbilityHandleList(const TArray<FGameplayAbilitySpecHandle>& InSpecHandleList);
	
	UBoxComponent* GetWeaponCollisionBox();
	
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetAbilityHandleList() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWarriorHeroWeaponData HeroWeaponData;
	
private:
	TArray<FGameplayAbilitySpecHandle> AbilityHandleList;
};
