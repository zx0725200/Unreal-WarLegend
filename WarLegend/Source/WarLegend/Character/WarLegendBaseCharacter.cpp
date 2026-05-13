// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarLegendBaseCharacter.h"

#include "Ability/HeroAbilitySystemComponent.h"
#include "Ability/Attribute/HeroAttributeSet.h"
#include "ETC/Define.h"

AWarLegendBaseCharacter::AWarLegendBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	// ? Decal 끄기
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

	// ? ability가 어디에 적용되고 누가 발동하는지 설정. 
	// ? GiveAbility() 호출하기 전에 반드시 해야 함.
	HeroAbilitySystemComponent->InitAbilityActorInfo(this,this);
}
