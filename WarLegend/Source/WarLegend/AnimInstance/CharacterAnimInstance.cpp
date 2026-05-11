// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

#include "Character/EnemyCharacter.h"
#include "Character/WarLegendCharacter.h"
#include "ETC/Define.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	MyCharacter = Cast<AWarLegendBaseCharacter>(TryGetPawnOwner());
	VALID_RETURN(MyCharacter);
	
	MyMovementComponent = MyCharacter->GetCharacterMovement();
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (!MyCharacter || !MyMovementComponent)
	{
		return;
	}
	
	GroundSpeed = MyCharacter->GetVelocity().Size2D();
	bAcceleration = MyMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f || GroundSpeed > 0.f;
	
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