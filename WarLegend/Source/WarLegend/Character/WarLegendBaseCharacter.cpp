// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarLegendBaseCharacter.h"

// Sets default values
AWarLegendBaseCharacter::AWarLegendBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWarLegendBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarLegendBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWarLegendBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

