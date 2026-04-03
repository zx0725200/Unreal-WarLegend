// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WarLegendBaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "WarLegendCharacter.generated.h"

class UBattleInputConfig;
enum class EPlayerLocType : uint8;
class UCameraComponent;
class USpringArmComponent;
class UCharAbilitySystemComponent;
class UCharAttributeSet;

UCLASS()
class WARLEGEND_API AWarLegendCharacter : public AWarLegendBaseCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWarLegendCharacter();

	void ChangeCamera(EPlayerLocType InMode);
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	void SetBattleCamera();
	void SetCityCamera();
	
	void ApplyCityMovement();
	void ApplyBattleMovement();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UCharAbilitySystemComponent> CharAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UCharAttributeSet> CharAttributeSet;
	
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

