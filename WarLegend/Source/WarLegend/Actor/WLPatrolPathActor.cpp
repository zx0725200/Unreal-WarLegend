// Fill out your copyright notice in the Description page of Project Settings.


#include "WLPatrolPathActor.h"

#include "ETC/Constant.h"


AWLPatrolPathActor::AWLPatrolPathActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Waypoints.Add(FVector(0.f, 0.f, 0.f));
	Waypoints.Add(FVector(0, Constant::MapSize, 0.f));
	Waypoints.Add(FVector(-Constant::MapSize, Constant::MapSize, 0));
	Waypoints.Add(FVector(-Constant::MapSize, 0.f, 0.f));
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

