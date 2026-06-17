// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BossMeleeHitNotify.generated.h"

/**
 * 보스 공격 몽타주의 타격 프레임에 배치하는 Notify.
 * 보스 전방으로 스피어 트레이스를 쏴서 적대 팀(플레이어)을 찾으면
 * GA_BossAttack 이 기다리는 HitEvent 를 발사한다.
 */
UCLASS()
class WARLEGEND_API UBossMeleeHitNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	// ? GA_BossAttack 의 HitEventTag 와 반드시 동일하게 맞춰야 함.
	UPROPERTY(EditAnywhere, Category = "Hit")
	FGameplayTag HitEventTag;

	// ? 트레이스 시작 소켓. 비워두면 액터 위치 기준.
	UPROPERTY(EditAnywhere, Category = "Hit")
	FName StartSocketName;

	// ? 보스 전방으로 트레이스 거리.
	UPROPERTY(EditAnywhere, Category = "Hit")
	float TraceLength = 150.f;

	// ? 트레이스 반경.
	UPROPERTY(EditAnywhere, Category = "Hit")
	float TraceRadius = 80.f;

	// ? 트레이스 시각화(디버그).
	UPROPERTY(EditAnywhere, Category = "Hit")
	bool bDrawDebug = false;
};
