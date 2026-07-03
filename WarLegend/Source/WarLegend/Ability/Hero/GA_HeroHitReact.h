// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Base/HeroAbility.h"
#include "GA_HeroHitReact.generated.h"

class UAnimMontage;

/**
 * 플레이어 피격 리액션 어빌리티.
 * Shared.Event.PlayerHit 이벤트로 트리거되며(=보스 공격에 맞으면), 발동되면
 *  1) 진행 중이던 공격을 끊고(CancelAbilitiesWithTag)
 *  2) Player.State.HitReacting 태그를 부착한 채 HitStunDuration 동안 유지 → 이 시간 동안
 *     공격/구르기 어빌리티가 막힌다(각 어빌리티의 ActivationBlockedTags 에 이 태그를 넣어둔다).
 *  3) HitReactMontage 를 재생(자르지 않아 자연스럽게 idle 로 블렌드).
 * HitStunDuration 이 지나면 태그를 떼고 종료 → 다시 행동 가능.
 */
UCLASS()
class WARLEGEND_API UGA_HeroHitReact : public UHeroAbility
{
	GENERATED_BODY()

public:
	UGA_HeroHitReact();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	// HitStunDuration 이 지나면 호출 → 종료(행동 재개).
	void OnStunFinished();

public:
	// 피격 애니. 비우면 애니 없이 HitStunDuration 동안 행동만 막는다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitReact")
	TObjectPtr<UAnimMontage> HitReactMontage;

	// 맞은 뒤 공격/구르기가 막히는 시간(초). "원하는 만큼"을 여기서 조절한다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitReact")
	float HitStunDuration = 0.6f;

private:
	FTimerHandle StunTimer;
};
