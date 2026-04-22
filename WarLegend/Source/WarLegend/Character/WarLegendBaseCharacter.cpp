// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarLegendBaseCharacter.h"

#include "Ability/HeroAbilitySystemComponent.h"
#include "Ability/HeroAttributeSet.h"

AWarLegendBaseCharacter::AWarLegendBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	GetMesh()->bReceivesDecals = false;
	
	HeroAbilitySystemComponent = CreateDefaultSubobject<UHeroAbilitySystemComponent>(TEXT("CharAbilitySystemComponent"));
	HeroAttributeSet = CreateDefaultSubobject<UHeroAttributeSet>(TEXT("HeroAttributeSet"));
}

UAbilitySystemComponent* AWarLegendBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWarriorAbilitySystemComponent();
}

void AWarLegendBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!HeroAbilitySystemComponent)
	{
		return;
	}
	
	HeroAbilitySystemComponent->InitAbilityActorInfo(this,this);
}
