// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_WeaponEquipBase.h"
#include "GA_UnequipWeapon.generated.h"

class AHeroWeaponBase;
class UInputMappingContext;
class UCharacterAnimLayer;
/**
 * 무기 해제: AnimLayer 언링크 / 입력 매핑 컨텍스트 제거 / 무기 어빌리티 제거.
 */
UCLASS()
class WARLEGEND_API UGA_UnequipWeapon : public UGA_WeaponEquipBase
{
	GENERATED_BODY()

protected:
	virtual void HandleWeapon(AHeroWeaponBase* InWeapon) override;

private:
	// 캐릭터에서 무기 전용 AnimLayer 링크 해제.
	void UnlinkWeaponAnimLayer(const TSubclassOf<UCharacterAnimLayer>& InAnimLayer);

	// 무기 입력 매핑 컨텍스트를 로컬 플레이어에서 제거.
	void RemoveWeaponMappingContext(UInputMappingContext* InMappingContext);

	// 무기에 저장된 어빌리티 핸들들을 ASC에서 제거.
	void RemoveWeaponAbilities(AHeroWeaponBase* InWeapon);
};
