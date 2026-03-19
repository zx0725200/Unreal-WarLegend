// Fill out your copyright notice in the Description page of Project Settings.


#include "WLPatrolPathActor.h"


AWLPatrolPathActor::AWLPatrolPathActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Waypoints.Add(FVector(0.f, 0.f, 0.f));
	Waypoints.Add(FVector(900.f, 0.f, 0.f));
	Waypoints.Add(FVector(900.f, 900.f, 0.f));
	Waypoints.Add(FVector(0.f, 900.f, 0.f));
}

int32 AWLPatrolPathActor::GetWaypointCount() const
{
	return Waypoints.Num();
}

FVector AWLPatrolPathActor::GetWaypointWorldLocation(int32 InIndex) const
{
	if (!Waypoints.IsValidIndex(InIndex))
	{
		return GetActorLocation();
	}
 
	// 로컬 좌표 → 월드 좌표 변환
	return GetActorTransform().TransformPosition(Waypoints[InIndex]);	
}

