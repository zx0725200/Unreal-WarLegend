// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HeroAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UHeroAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	// ? Anim 에서 Notify 올때 호출.
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	// Anim -> Notify 태그 설정.
	UPROPERTY(EditAnywhere, Category = "Event")
	FGameplayTag EventTag;
};
