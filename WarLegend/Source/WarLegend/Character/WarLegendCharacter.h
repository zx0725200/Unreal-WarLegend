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

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
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
};

