// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

#include "Character/EnemyCharacter.h"
#include "Character/WarLegendCharacter.h"
#include "ETC/Define.h"
#include "GameFramework/CharacterMovementComponent.h"

namespace
{
	// 캐릭터 정면 기준 이동 방향 각도(-180~180). 0=앞, +90=오른쪽, -90=왼쪽, ±180=뒤.
	float CalculateMoveDirection(const FVector& Velocity, const FRotator& BaseRotation)
	{
		if (Velocity.IsNearlyZero())
		{
			return 0.f;
		}

		const FVector Forward = BaseRotation.Vector();
		const FVector Right = FRotationMatrix(BaseRotation).GetScaledAxis(EAxis::Y);
		const FVector VelDir = Velocity.GetSafeNormal2D();

		const float ForwardDot = FVector::DotProduct(Forward, VelDir);
		const float RightDot = FVector::DotProduct(Right, VelDir);
		return FMath::RadiansToDegrees(FMath::Atan2(RightDot, ForwardDot));
	}
}

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	MyCharacter = Cast<AWarLegendBaseCharacter>(TryGetPawnOwner());
	VALID_RETURN(MyCharacter);

	MyMovementComponent = MyCharacter->GetCharacterMovement();

	// 플레이어면 캐싱(락온 조회용). 적이면 null 이라 락온 관련 값은 항상 기본값.
	MyHeroCharacter = Cast<AWarLegendCharacter>(MyCharacter);
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (!MyCharacter || !MyMovementComponent)
	{
		return;
	}
	
	const FVector Velocity = MyCharacter->GetVelocity();
	GroundSpeed = Velocity.Size2D();
	bAcceleration = MyMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f || GroundSpeed > 0.f;

	// 락온 여부(플레이어만) + 정면 기준 이동 방향 각도 계산.
	bIsLockedOn = MyHeroCharacter ? MyHeroCharacter->IsLockedOn() : false;
	Direction = CalculateMoveDirection(Velocity, MyCharacter->GetActorRotation());

	if (bAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;

		bShouldEnterRelaxState = (IdleElapsedTime >= WaitingRelaxState);
	}
}