// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TimerHandle.h"
#include "ViewModelBase.h"
#include "HudPlayerHpVM.generated.h"

struct FOnAttributeChangeData;
class UAbilitySystemComponent;
/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHpRatioChanged, float, NewValue);

UCLASS()
class WARLEGEND_API UHudPlayerHpVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void ClearBinding() override;

	float GetCurrentHp() const { return CurrentHp; }
	float GetMaxHp() const { return MaxHp; }
	float GetHpRatio() const { return HpRatio; }
	FOnPlayerHpRatioChanged& GetOnHpChanged() { return OnHpRatioChanged; }

private:
	// ? 플레이어 폰/ASC 가 준비될 때까지 시도(준비 전이면 짧게 재시도).
	void TryBindPlayer();

	void SetCurrentHp(const float InValue);
	void SetMaxHp(const float InValue);
	void SetHpRatio(const float InValue);

	void HandleCurrentHpChanged(const FOnAttributeChangeData& Data);
	void HandleMaxHpChanged(const FOnAttributeChangeData& Data);

private:
	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> CachedASC;

	UPROPERTY()
	FOnPlayerHpRatioChanged OnHpRatioChanged;

	float CurrentHp = 0.f;
	float MaxHp = 1.f;
	float HpRatio = 0.f;

	FDelegateHandle CurrentHpHandle;
	FDelegateHandle MaxHpHandle;

	FTimerHandle RetryTimer;
	int32 RetryCount = 0;
};
