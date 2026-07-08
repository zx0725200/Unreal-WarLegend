// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_WeaponEquipBase.h"

#include "EnhancedInputSubsystems.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Actor/HeroWeaponBase.h"
#include "Component/HeroCombatComponent.h"
#include "Controller/WarLegendPlayerController.h"
#include "ETC/Define.h"

void UGA_WeaponEquipBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 노티파이 이벤트 대기(부착 타이밍).
	UAbilityTask_WaitGameplayEvent* WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EventTag, nullptr, false, true);
	WaitEventTask->EventReceived.AddDynamic(this, &UGA_WeaponEquipBase::OnWeaponEventReceived);
	WaitEventTask->ReadyForActivation();

	// 몽타주 재생.
	UAbilityTask_PlayMontageAndWait* MontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, Montage);
	MontageTask->OnCompleted.AddDynamic(this, &UGA_WeaponEquipBase::OnMontageEnded);
	MontageTask->OnInterrupted.AddDynamic(this, &UGA_WeaponEquipBase::OnMontageEnded);
	MontageTask->OnCancelled.AddDynamic(this, &UGA_WeaponEquipBase::OnMontageEnded);
	MontageTask->ReadyForActivation();
}

void UGA_WeaponEquipBase::OnMontageEnded()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_WeaponEquipBase::OnWeaponEventReceived(FGameplayEventData Payload)
{
	UHeroCombatComponent* CombatComp = GetHeroCombatComponentFromActorInfo();
	USkeletalMeshComponent* SkeMesh = GetActorInfo().SkeletalMeshComponent.Get();
	VALID_RETURN(CombatComp, SkeMesh);

	AHeroWeaponBase* Weapon = CombatComp->GetHeroCarriedWeaponByTag(WeaponTag);
	VALID_RETURN(Weapon);

	// 소켓에 무기 부착.
	const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
	Weapon->AttachToComponent(SkeMesh, AttachRules, SocketNameToAttach);

	// 무기별 실제 처리는 파생 클래스에 위임.
	HandleWeapon(Weapon);
}

UEnhancedInputLocalPlayerSubsystem* UGA_WeaponEquipBase::GetHeroInputSubsystem()
{
	AWarLegendPlayerController* PC = GetHeroControllerFromActorInfo();
	if (!PC)
	{
		return nullptr;
	}

	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer)
	{
		return nullptr;
	}

	return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
}
