// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HeroWeaponNotifyState.generated.h"

UENUM()
enum ECollision : uint8
{
	OnCollision = 0,
	OffCollision,
};

/**
 * 
 */
UCLASS()
class WARLEGEND_API UHeroWeaponNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	void ToggleWeaponCollision(const USkeletalMeshComponent* InMeshComp, const ECollisionEnabled::Type InCollisionType);
};
