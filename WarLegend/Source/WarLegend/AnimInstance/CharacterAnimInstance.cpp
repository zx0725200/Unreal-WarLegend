// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

#include "Character/WarLegendCharacter.h"
#include "ETC/Define.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	MyCharacter = Cast<AWarLegendCharacter>(TryGetPawnOwner());
	VALID_RETURN(MyCharacter);
	
	MyMovementComponent = MyCharacter->GetCharacterMovement();
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	VALID_RETURN(MyCharacter, MyMovementComponent);
	
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	GroundSpeed = MyCharacter->GetVelocity().Size2D();
	
	bAcceleration = MyMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
