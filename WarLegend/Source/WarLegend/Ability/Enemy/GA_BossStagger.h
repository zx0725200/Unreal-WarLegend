// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Base/EnemyAbility.h"
#include "GA_BossStagger.generated.h"

class UAnimMontage;

/**
 * 패링당한 보스의 경직(그로기) 리액션 어빌리티.
 * Shared.Event.BossStagger 이벤트로 트리거되며, 발동되면
 *  1) 진행 중이던 공격 어빌리티(Enemy.Ability.Attack.*)를 취소해 하던 모션을 끊고
 *  2) Enemy.State.Groggy 태그를 부착한 채 StaggerMontage 를 재생하고
 *  3) ParryCueTag GameplayCue 를 보스(또는 충돌) 위치에 터뜨려 이펙트/사운드를 낸다.
 * 몽타주는 중간에 자르지 않고 끝까지 재생해 자연스럽게 idle 로 블렌드되며,
 * 공격 금지(경직)는 max(GroggyDuration, 몽타주 길이) 동안 유지한 뒤 태그를 떼고 종료한다.
 */
UCLASS()
class WARLEGEND_API UGA_BossStagger : public UEnemyAbility
{
	GENERATED_BODY()

public:
	UGA_BossStagger();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	// GroggyDuration 타이머가 끝나면 호출.
	void OnGroggyTimerElapsed();

	// 스태거 몽타주가 끝/블렌드아웃/중단되면 호출.
	UFUNCTION()
	void OnStaggerMontageEnded();

	// 몽타주도 끝나고 경직 시간도 지났을 때만 어빌리티를 종료한다(둘 중 늦은 쪽 기준).
	void TryFinish();

public:
	// 경직 시 재생할 그로기 모션. 비우면 GroggyDuration 동안 태그만 유지하고 끝낸다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stagger")
	TObjectPtr<UAnimMontage> StaggerMontage;

	// 패링당한 보스가 경직(공격 불가) 상태로 멈춰 있을 시간(초). 이 값이 '뜸 들이는 시간'을 정한다.
	// 몽타주 길이와 무관하게 이 값만큼 다음 공격을 못 한다. 키우면 패링 후 더 오래 멈칫.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stagger")
	float GroggyDuration = 1.0f;

	// 패링 성공 시 터뜨릴 GameplayCue 태그(이펙트/사운드는 GameplayCueNotify 에서 처리).
	// 기본값은 생성자에서 GameplayCue.Parry 로 설정. 비우면 큐 미발동.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stagger")
	FGameplayTag ParryCueTag;

private:
	FTimerHandle GroggyTimer;

	// 종료 조건 추적: 몽타주가 끝났는지 / 경직 시간이 지났는지. 둘 다 true 여야 종료.
	bool bMontageEnded = false;
	bool bGroggyElapsed = false;
};
