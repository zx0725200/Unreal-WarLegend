// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_SpawnWeapon.h"
#include "Actor/HeroWeaponBase.h"
#include "Component/HeroCombatComponent.h"


UGA_SpawnWeapon::UGA_SpawnWeapon()
{
	// SpawnActor는 권한 있는 곳에서만 호출되어야 클라 간 일관성이 유지.
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_SpawnWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	AHeroWeaponBase* WeaponActor = SpawnWeaponActor();
	USkeletalMeshComponent* SkeMesh = GetActorInfo().SkeletalMeshComponent.Get();
	UHeroCombatComponent* CombatComp = GetHeroCombatComponentFromActorInfo();
	if (!WeaponActor || !SkeMesh || !CombatComp)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	AttachToHero(SkeMesh, WeaponActor);
	
	CombatComp->RegisterSpawnedWeapon(WeaponTag, WeaponActor, bRegister);
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGA_SpawnWeapon::AttachToHero(USkeletalMeshComponent* InHero, AHeroWeaponBase* InWeapon) const
{
	const FAttachmentTransformRules AttachRules(
			EAttachmentRule::SnapToTarget,    // Location
			EAttachmentRule::KeepRelative,    // Rotation
			EAttachmentRule::KeepWorld,       // Scale
			/*bWeldSimulatedBodies=*/ true);
	
	InWeapon->AttachToComponent(InHero, AttachRules, SocketNameToAttach);
}

AHeroWeaponBase* UGA_SpawnWeapon::SpawnWeaponActor()
{
	// 무기 Spawn
	APawn* OwnerPawn = Cast<APawn>(GetAvatarActorFromActorInfo());
	UWorld* World = GetWorld();
	
	if (!OwnerPawn || !World || !WeaponClass)
	{
		return nullptr;
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = OwnerPawn;
	SpawnParameters.Instigator = OwnerPawn;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	AHeroWeaponBase* WeaponActor = World->SpawnActor<AHeroWeaponBase>(WeaponClass, FTransform::Identity, SpawnParameters);
	if (!IsValid(WeaponActor))
	{
		return nullptr;
	}
	
	return WeaponActor;
}
