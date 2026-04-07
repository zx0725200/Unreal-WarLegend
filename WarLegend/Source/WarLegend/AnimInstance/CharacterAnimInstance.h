// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimInstanceBase.h"
#include "CharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AWarLegendCharacter;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UCharacterAnimInstance : public UCharacterAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	TObjectPtr<AWarLegendCharacter> MyCharacter;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	TObjectPtr<UCharacterMovementComponent> MyMovementComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool bAcceleration;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WaitingRelaxState = 5.f;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool bShouldEnterRelaxState;
	
	float IdleElapsedTime;
};
