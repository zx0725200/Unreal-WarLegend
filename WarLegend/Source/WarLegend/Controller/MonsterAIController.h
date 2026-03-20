// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

class AWLPatrolPathActor;
class AMonster;

UCLASS()
class WARLEGEND_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMonsterAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
 
private:
	void MoveToNextWaypoint();
 
	UFUNCTION()
	virtual void OnMoveCompleted(const FAIRequestID RequestID, const EPathFollowingResult::Type Result) override;

private:
	UPROPERTY()
	TObjectPtr<AMonster> CachedMonster;
 
	UPROPERTY()
	TObjectPtr<AWLPatrolPathActor> CachedPatrolPath;
};
