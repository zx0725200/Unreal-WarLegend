// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WarLegendBaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "WarLegendCharacter.generated.h"

class UCharDataConfig;
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
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
private:
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
};

