// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "HudBossHpVM.generated.h"

struct FOnAttributeChangeData;
class UAbilitySystemComponent;
/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChanged, float, NewValue);

UCLASS()
class WARLEGEND_API UHudBossHpVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void ClearBinding() override;

	float GetCurrentHp() const { return CurrentHp; }
	float GetMaxHp() const { return MaxHp; }
	float GetHpRatio() const { return HpRatio; }

private:
	void SetCurrentHp(float InValue);
	void SetMaxHp(float InValue);
	void SetHpRatio(float InValue);

	void HandleCurrentHpChanged(const FOnAttributeChangeData& Data);
	void HandleMaxHpChanged(const FOnAttributeChangeData& Data);

public:
	UPROPERTY(BlueprintAssignable)
	FOnValueChanged OnCurrentHpChange;

	UPROPERTY(BlueprintAssignable)
	FOnValueChanged OnMaxHpChange;

	UPROPERTY(BlueprintAssignable)
	FOnValueChanged OnHpRatioChanged;

private:
	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> CachedASC;

	float CurrentHp = 0.f;
	float MaxHp = 1.f;
	float HpRatio = 0.f;

	FDelegateHandle CurrentHpHandle;
	FDelegateHandle MaxHpHandle;
};
