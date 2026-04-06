// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WarLegendBaseCharacter.h"
#include "WarLegendCharacter.generated.h"

class UCharCombatComponent;
struct FStreamableHandle;
class UCharDataConfigBase;
class UBattleInputConfig;
enum class EPlayerLocType : uint8;
class UCameraComponent;
class USpringArmComponent;
class UCharAbilitySystemComponent;
class UCharAttributeSet;

UCLASS()
class WARLEGEND_API AWarLegendCharacter : public AWarLegendBaseCharacter
{
	GENERATED_BODY()

public:
	AWarLegendCharacter();

	void ChangeCamera(EPlayerLocType InMode);
	
	UCharCombatComponent* GetCharCombatComponent();

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
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
	TObjectPtr<UCharCombatComponent> CharCombatComponent;
	
	TSharedPtr<FStreamableHandle> DataLoadHandle;
};

