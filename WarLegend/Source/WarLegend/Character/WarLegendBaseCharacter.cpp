// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarLegendBaseCharacter.h"

#include "Ability/HeroAbilitySystemComponent.h"
#include "Ability/Attribute/HeroAttributeSet.h"
#include "ETC/Define.h"

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
	return GetHeroAbilitySystemComponent();
}

UPawnCombatComponentBase* AWarLegendBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

void AWarLegendBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	VALID_RETURN(HeroAbilitySystemComponent);

	HeroAbilitySystemComponent->InitAbilityActorInfo(this,this);
}
