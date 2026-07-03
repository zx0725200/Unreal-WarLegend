// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimInstanceBase.h"
#include "CharacterAnimInstance.generated.h"

class AWarLegendBaseCharacter;
class AWarLegendCharacter;
class UCharacterMovementComponent;
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
	TObjectPtr<AWarLegendBaseCharacter> MyCharacter;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	TObjectPtr<UCharacterMovementComponent> MyMovementComponent;

	// 플레이어일 때만 유효(락온 조회용). 적이면 null.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	TObjectPtr<AWarLegendCharacter> MyHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool bAcceleration;

	// 락온 중이면 true → AnimBP 에서 스트레이프(방향별) 로코모션으로 전환.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool bIsLockedOn;

	// 캐릭터 정면 기준 이동 방향 각도(-180~180). 0=앞, 90=오른쪽, -90=왼쪽, ±180=뒤.
	// 락온 스트레이프 블렌드스페이스의 X축으로 사용.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float Direction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WaitingRelaxState = 5.f;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool bShouldEnterRelaxState;
	
	float IdleElapsedTime;
};
