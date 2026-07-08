// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Ability/Base/HeroAbility.h"
#include "GA_WeaponEquipBase.generated.h"

struct FGameplayEventData;
struct FGameplayAbilityActivationInfo;
struct FGameplayAbilitySpecHandle;
class AHeroWeaponBase;
class UAnimMontage;
class UEnhancedInputLocalPlayerSubsystem;
/**
 * 무기 장착/해제 어빌리티의 공통 베이스.
 * 몽타주 재생 → 노티파이 이벤트 대기 → 무기 찾기/부착 → HandleWeapon() 순서의 뼈대를 제공한다.
 * 파생 클래스는 HandleWeapon()에서 무기별 실제 처리(링크/언링크 등)만 구현한다.
 */
UCLASS(Abstract)
class WARLEGEND_API UGA_WeaponEquipBase : public UHeroAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	// 파생 클래스가 구현: 부착된 무기에 대한 실제 장착/해제 처리.
	virtual void HandleWeapon(AHeroWeaponBase* InWeapon) {}
	
	UEnhancedInputLocalPlayerSubsystem* GetHeroInputSubsystem();

private:
	// 노티파이가 보낸 이벤트 수신 시 무기 찾기 + 소켓 부착 후 HandleWeapon() 호출.
	UFUNCTION()
	void OnWeaponEventReceived(FGameplayEventData Payload);
	
	UFUNCTION()
	void OnMontageEnded();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UAnimMontage> Montage;

	// 노티파이가 보내는 이벤트 태그
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (Categories = "Player.Event"))
	FGameplayTag EventTag;

	// 소지 무기를 찾는 태그
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (Categories = "Player.Weapon"))
	FGameplayTag WeaponTag;

	// 무기를 부착할 소켓 이름 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName SocketNameToAttach;
};
