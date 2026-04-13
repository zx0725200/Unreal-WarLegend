// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonAbilityBase.h"
#include "AbilitySystemComponent.h"
#include "HeroAbilitySystemComponent.h"
#include "Component/HeroCombatComponent.h"

UHeroCombatComponent* UCommonAbilityBase::GetHeroCombatComponentFromActorInfo() const
{
	const AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (AvatarActor == nullptr)
	{
		return nullptr;
	}
	
	return AvatarActor->FindComponentByClass<UHeroCombatComponent>();
}

UHeroAbilitySystemComponent* UCommonAbilityBase::GetHeroAbilityComponentFromActorInfo() const
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (AbilitySystemComponent == nullptr)
	{
		return nullptr;
	}
	
	return Cast<UHeroAbilitySystemComponent>(AbilitySystemComponent);
}
