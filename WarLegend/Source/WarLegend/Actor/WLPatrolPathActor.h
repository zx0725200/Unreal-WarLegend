// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WLPatrolPathActor.generated.h"

UCLASS()
class WARLEGEND_API AWLPatrolPathActor : public AActor
{
	GENERATED_BODY()

public:
	AWLPatrolPathActor();

public:
	UFUNCTION(BlueprintCallable, Category = "Patrol")
	int32 GetWaypointCount() const;
	
	UFUNCTION(BlueprintCallable, Category = "Patrol")
	FVector GetWaypointWorldLocation(const int32 InIndex) const;
 
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (MakeEditWidget = true))
	TArray<FVector> Waypoints;
};
