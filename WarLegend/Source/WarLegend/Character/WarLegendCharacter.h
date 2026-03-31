// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WarLegendBaseCharacter.h"
#include "WarLegendCharacter.generated.h"

enum class ECameraMode : uint8;
class UCameraComponent;
class USpringArmComponent;

UCLASS(abstract)
class AWarLegendCharacter : public AWarLegendBaseCharacter
{
	GENERATED_BODY()

public:
	AWarLegendCharacter();

	void ChangeCamera(ECameraMode InMode);
	
private:
	void SetBattleCamera();
	void SetCityCamera();
	
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

