// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnComponent.h"

#include "AbilitySystemComponent.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Ability/Attribute/HeroAttributeSet.h"
#include "Character/EnemyCharacter.h"

ULockOnComponent::ULockOnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// 락온 중일 때만 틱을 켠다(StartLockOn/StopLockOn 에서 토글).
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 타겟이 죽었거나 너무 멀어졌으면 자동 해제.
	if (!IsTargetStillValid(CurrentTarget.Get()))
	{
		StopLockOn();
		return;
	}

	UpdateControlRotation(DeltaTime);
}

void ULockOnComponent::ToggleLockOn()
{
	if (IsLockedOn())
	{
		StopLockOn();
		return;
	}

	if (AActor* Target = FindBestTarget())
	{
		StartLockOn(Target);
	}
}

AActor* ULockOnComponent::FindBestTarget() const
{
	const ACharacter* OwnerChar = GetOwnerCharacter();
	const AController* Controller = GetOwnerController();
	UWorld* World = GetWorld();
	if (!OwnerChar || !Controller || !World) return nullptr;

	// 카메라 시점 기준으로 '화면 중앙에 가장 가까운' 적을 고른다.
	FVector CamLoc;
	FRotator CamRot;
	Controller->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector CamForward = CamRot.Vector();

	AActor* Best = nullptr;
	float BestDot = -1.f;

	for (TActorIterator<AEnemyCharacter> It(World); It; ++It)
	{
		AEnemyCharacter* Enemy = *It;
		if (!IsValid(Enemy)) continue;

		// 사망한 적 제외.
		if (const UAbilitySystemComponent* ASC = Enemy->GetAbilitySystemComponent())
		{
			if (ASC->GetNumericAttribute(UHeroAttributeSet::GetCurrentHpAttribute()) <= 0.f)
			{
				continue;
			}
		}

		const FVector ToEnemy = Enemy->GetActorLocation() - OwnerChar->GetActorLocation();
		const float Distance = ToEnemy.Size();
		if (Distance > MaxLockOnDistance || Distance <= KINDA_SMALL_NUMBER) continue;

		// 카메라 정면 쪽에 있는지(화면 안) + 중앙에 가까운지.
		const float FacingDot = FVector::DotProduct(CamForward, ToEnemy.GetSafeNormal());
		if (FacingDot < MinFacingDot) continue;

		// 벽 뒤 제외.
		if (bRequireLineOfSight)
		{
			FHitResult Hit;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(OwnerChar);
			Params.AddIgnoredActor(Enemy);
			const bool bBlocked = World->LineTraceSingleByChannel(
				Hit, CamLoc, Enemy->GetActorLocation(), ECC_Visibility, Params);
			if (bBlocked) continue;
		}

		if (FacingDot > BestDot)
		{
			BestDot = FacingDot;
			Best = Enemy;
		}
	}

	return Best;
}

void ULockOnComponent::StartLockOn(AActor* NewTarget)
{
	if (!NewTarget) return;

	CurrentTarget = NewTarget;

	// 타겟 위에 락온 마커 표시.
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(NewTarget))
	{
		Enemy->SetLockOnMarkerVisible(true);
	}

	// 스트레이프 이동으로 전환: 캐릭터가 컨트롤 회전(=타겟 방향)을 바라보게.
	if (ACharacter* OwnerChar = GetOwnerCharacter())
	{
		OwnerChar->bUseControllerRotationYaw = true;
		if (UCharacterMovementComponent* MoveComp = OwnerChar->GetCharacterMovement())
		{
			MoveComp->bOrientRotationToMovement = false;
		}
	}

	SetComponentTickEnabled(true);
}

void ULockOnComponent::StopLockOn()
{
	// 타겟의 락온 마커 숨김(초기화 전에).
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(CurrentTarget.Get()))
	{
		Enemy->SetLockOnMarkerVisible(false);
	}

	CurrentTarget.Reset();

	// 배틀 기본 이동으로 복귀: 이동 방향으로 자동 회전.
	if (ACharacter* OwnerChar = GetOwnerCharacter())
	{
		OwnerChar->bUseControllerRotationYaw = false;
		if (UCharacterMovementComponent* MoveComp = OwnerChar->GetCharacterMovement())
		{
			MoveComp->bOrientRotationToMovement = true;
		}
	}

	SetComponentTickEnabled(false);
}

bool ULockOnComponent::IsTargetStillValid(const AActor* Target) const
{
	if (!IsValid(Target)) return false;

	const ACharacter* OwnerChar = GetOwnerCharacter();
	if (!OwnerChar) return false;

	// 거리 초과 시 해제.
	const float Distance = FVector::Dist(OwnerChar->GetActorLocation(), Target->GetActorLocation());
	if (Distance > MaxLockOnDistance * BreakDistanceMultiplier) return false;

	// 사망 시 해제.
	if (const AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Target))
	{
		if (const UAbilitySystemComponent* ASC = Enemy->GetAbilitySystemComponent())
		{
			if (ASC->GetNumericAttribute(UHeroAttributeSet::GetCurrentHpAttribute()) <= 0.f)
			{
				return false;
			}
		}
	}

	return true;
}

void ULockOnComponent::UpdateControlRotation(float DeltaTime)
{
	AController* Controller = GetOwnerController();
	const ACharacter* OwnerChar = GetOwnerCharacter();
	const AActor* Target = CurrentTarget.Get();
	if (!Controller || !OwnerChar || !Target) return;

	// 좌우(Yaw)만 타겟을 향하게 하고 상하(Pitch)는 원래 카메라 각도를 그대로 유지한다.
	const FRotator Current = Controller->GetControlRotation();
	const float DesiredYaw = (Target->GetActorLocation() - OwnerChar->GetActorLocation()).Rotation().Yaw;

	const FRotator TargetRot(Current.Pitch, DesiredYaw, 0.f);

	// 급격히 꺾이지 않게 부드럽게 보간(피치는 그대로라 실제로는 Yaw만 돈다).
	const FRotator NewRot = FMath::RInterpTo(Current, TargetRot, DeltaTime, InterpSpeed);
	Controller->SetControlRotation(NewRot);
}

ACharacter* ULockOnComponent::GetOwnerCharacter() const
{
	return Cast<ACharacter>(GetOwner());
}

AController* ULockOnComponent::GetOwnerController() const
{
	const ACharacter* OwnerChar = GetOwnerCharacter();
	return OwnerChar ? OwnerChar->GetController() : nullptr;
}
