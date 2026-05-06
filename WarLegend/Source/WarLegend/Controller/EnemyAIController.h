// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;

UCLASS()
class WARLEGEND_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION() 
	void OnTargetPerceptionUpdated(AActor* InActor, FAIStimulus InStimulus);
	
public:
	UPROPERTY(EditDefaultsOnly) 
	TObjectPtr<UBehaviorTree> BTAsset;
	
	UPROPERTY(VisibleAnywhere) 
	TObjectPtr<UAIPerceptionComponent> Perception;
	
	UPROPERTY(VisibleAnywhere) 
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
};
