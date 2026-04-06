// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarLegendBaseCharacter.h"

#include "Ability/CharAbilitySystemComponent.h"
#include "Ability/CharAttributeSet.h"

AWarLegendBaseCharacter::AWarLegendBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	GetMesh()->bReceivesDecals = false;
	
	CharAbilitySystemComponent = CreateDefaultSubobject<UCharAbilitySystemComponent>(TEXT("CharAbilitySystemComponent"));
	CharAttributeSet = CreateDefaultSubobject<UCharAttributeSet>(TEXT("CharAttributeSet"));
}

UAbilitySystemComponent* AWarLegendBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWarriorAbilitySystemComponent();
}

void AWarLegendBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!CharAbilitySystemComponent)
	{
		return;
	}
	
	CharAbilitySystemComponent->InitAbilityActorInfo(this,this);
}
