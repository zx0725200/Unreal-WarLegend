// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommonTriggerActor.generated.h"

class UBoxComponent;

UCLASS()
class WARLEGEND_API ACommonTriggerActor : public AActor
{
	GENERATED_BODY()

public:
	ACommonTriggerActor();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTriggerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// 여러 트리거가 생길수도 있기 때문에 확장성을 위해 함수 제작.
	void ExecuteTriggerByType();
	
	// -- 트리거에 따른 함수 분리. 
	void OpenDungeonMenu() const;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr <UBoxComponent> Trigger;
};
