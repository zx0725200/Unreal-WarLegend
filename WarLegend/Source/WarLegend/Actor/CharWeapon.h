// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharWeaponBase.h"
#include "GameplayAbilitySpecHandle.h"
#include "CharWeapon.generated.h"

UCLASS()
class WARLEGEND_API ACharWeapon : public ACharWeaponBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetAbilityHandleList(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetAbilityHandleList() const;

private:
	TArray<FGameplayAbilitySpecHandle> AbilityHandleList;
};
