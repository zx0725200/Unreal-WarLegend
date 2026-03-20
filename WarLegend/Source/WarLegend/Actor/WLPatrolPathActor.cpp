// Fill out your copyright notice in the Description page of Project Settings.


#include "WLPatrolPathActor.h"


AWLPatrolPathActor::AWLPatrolPathActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Waypoints.Add(FVector(0.f, 0.f, 0.f));
	Waypoints.Add(FVector(0, 1800.f, 0.f));
	Waypoints.Add(FVector(-1800.f, 1800.f, 0));
	Waypoints.Add(FVector(-1800.f, 0.f, 0.f));
}

int32 AWLPatrolPathActor::GetWaypointCount() const
{
	return Waypoints.Num();
}

FVector AWLPatrolPathActor::GetWaypointWorldLocation(const int32 InIndex) const
{
	if (!Waypoints.IsValidIndex(InIndex))
	{
		return GetActorLocation();
	}
	
	return GetActorTransform().TransformPosition(Waypoints[InIndex]);	
}

