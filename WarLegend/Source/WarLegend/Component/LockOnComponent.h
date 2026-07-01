// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"

class ACharacter;
class AController;

/**
 * 플레이어 캐릭터에 붙는 락온(타겟팅) 컴포넌트.
 * ToggleLockOn() 으로 켜면 화면 앞쪽의 가장 적절한 적을 타겟으로 잡고,
 *  - 매 틱 컨트롤 회전을 타겟 방향으로 보간 → 스프링암(bUsePawnControlRotation)이 따라가 카메라가 타겟을 본다.
 *  - 무브먼트를 스트레이프로 전환(bUseControllerRotationYaw=true) → 캐릭터가 타겟을 바라보며 이동한다.
 * 타겟이 죽거나 너무 멀어지면 자동 해제된다.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARLEGEND_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULockOnComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 락온 토글: 잠겨 있으면 해제, 아니면 최적 타겟을 찾아 잠금.
	void ToggleLockOn();

	bool IsLockedOn() const { return CurrentTarget.IsValid(); }
	AActor* GetCurrentTarget() const { return CurrentTarget.Get(); }

private:
	AActor* FindBestTarget() const;
	void StartLockOn(AActor* NewTarget);
	void StopLockOn();
	bool IsTargetStillValid(const AActor* Target) const;
	void UpdateControlRotation(float DeltaTime);

	ACharacter* GetOwnerCharacter() const;
	AController* GetOwnerController() const;

public:
	// 이 거리 안의 적만 락온 후보.
	UPROPERTY(EditAnywhere, Category = "LockOn")
	float MaxLockOnDistance = 1500.f;

	// 락온 유지 한계 = MaxLockOnDistance * 이 배수. 넘으면 자동 해제(약간의 여유).
	UPROPERTY(EditAnywhere, Category = "LockOn")
	float BreakDistanceMultiplier = 1.3f;

	// 카메라 정면 기준 후보 허용 각도(Dot). 0 = 정면 90도 이내, 클수록 더 정면만.
	UPROPERTY(EditAnywhere, Category = "LockOn")
	float MinFacingDot = 0.f;

	// 컨트롤 회전(Yaw)이 타겟을 향해 돌아가는 속도. 상하 각도는 건드리지 않음.
	UPROPERTY(EditAnywhere, Category = "LockOn")
	float InterpSpeed = 11.f;

	// 벽 뒤의 적을 락온하지 않도록 시야(라인트레이스) 검사.
	UPROPERTY(EditAnywhere, Category = "LockOn")
	bool bRequireLineOfSight = true;

private:
	TWeakObjectPtr<AActor> CurrentTarget;
};
