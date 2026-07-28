// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WarLegendBaseCharacter.h"
#include "WarLegendCharacter.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UHeroCombatComponent;
class ULockOnComponent;
struct FStreamableHandle;
class UCommonAbilityConfigBase;
class UHeroBattleInputConfig;
enum class EPlayerLocType : uint8;
class UCameraComponent;
class USpringArmComponent;
class UHeroAbilitySystemComponent;
class UHeroAttributeSet;
class UNiagaraSystem;
class UCameraShakeBase;

UCLASS()
class WARLEGEND_API AWarLegendCharacter : public AWarLegendBaseCharacter
{
	GENERATED_BODY()

public:
	AWarLegendCharacter();

	void ChangeCamera(EPlayerLocType InMode);

	UHeroCombatComponent* GetHeroCombatComponent();

	// 락온 토글(컨트롤러 입력에서 호출).
	void ToggleLockOn();
	// 락온 중이면 true(락온 중엔 마우스 프리룩을 무시하기 위해 컨트롤러가 조회).
	bool IsLockedOn() const;

	// 던전 입장 연출 시작: 상공 텔레포트 직후 호출되어 낙하 상태로 전환하고 착지 이펙트를 예약한다.
	void BeginDungeonEntry();

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual UPawnCombatComponentBase* GetPawnCombatComponent() const override;
	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(0); }
	
private:
	void LoadBattleMode();
	void ApplyBattleMode();
	
	void SetBattleCamera();
	void SetCityCamera();
	void ApplyCityMovement();
	void ApplyBattleMovement();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> BattleCameraArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> TopDownCameraArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> BattleCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHeroCombatComponent> HeroCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LockOn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULockOnComponent> LockOnComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AIPerception", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionStimuliSourceComponent> StimuliSource;

	TSharedPtr<FStreamableHandle> DataLoadHandle;

	// 던전 입장 낙하 착지 시 발밑에 재생할 이펙트(BP에서 지정).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dungeon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> LandingEffect;

	// 착지 시 카메라 쉐이크(BP에서 지정).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dungeon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> LandingCameraShake;

	// 입장 연출 낙하 중인지. 일반 점프 착지와 구분해 첫 착지에만 이펙트를 재생하기 위한 플래그.
	bool bDungeonEntrySequence = false;
};

