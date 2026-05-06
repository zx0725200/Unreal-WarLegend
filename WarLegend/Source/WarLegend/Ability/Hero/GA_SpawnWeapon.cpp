// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_SpawnWeapon.h"

#include "Actor/HeroWeaponBase.h"

void UGA_SpawnWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	const auto Owner = GetAvatarActorFromActorInfo();
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Owner;
	SpawnParameters.Instigator = Cast<APawn>(Owner);
	
	UWorld * world = GetWorld();
	world->SpawnActor(AHeroWeaponBase::StaticClass(), nullptr, nullptr, SpawnParameters);
	
	
}
