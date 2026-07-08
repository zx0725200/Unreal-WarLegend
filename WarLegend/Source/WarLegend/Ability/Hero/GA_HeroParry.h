// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Base/HeroAbility.h"
#include "GA_HeroParry.generated.h"

class UAnimMontage;

/**
 * 우클릭으로 발동하는 패링 어빌리티.
 * 발동되면 ParryWindowDuration(기본 0.5초) 동안 플레이어 ASC 에
 * Player.State.Parrying 태그를 부착한다. 보스 타격이 그 시간 안에 들어오면
 * GA_BossAttack 이 태그를 보고 데미지를 무효화한다(= 패링 성공).
 */
UCLASS()
class WARLEGEND_API UGA_HeroParry : public UHeroAbility
{
	GENERATED_BODY()

public:
	UGA_HeroParry();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;

private:
	UFUNCTION()
	void OnMontageFinished();

	// 윈도우 시간이 끝나면 호출 -> 패링 상태 태그 제거.
	void CloseParryWindow();

public:
	// 패링 모션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parry")
	TObjectPtr<UAnimMontage> ParryMontage;

	// 우클릭 후 패링이 유효한 시간(초). 보스 타격이 이 안에 들어오면 무피해.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parry")
	float ParryDuration = 0.5f;

private:
	FTimerHandle ParryTimer;
};
