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
	// Sets default values for this actor's properties
	ACommonTriggerActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnTriggerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void SetTriggerAction();
	
	void OpenDungeonMenu();
	void MoveToBossPosition();
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr <UBoxComponent> Trigger;
};
