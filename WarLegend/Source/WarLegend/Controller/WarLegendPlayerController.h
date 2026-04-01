// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
//#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "WarLegendPlayerController.generated.h"

struct FInputActionValue;
class UBattleInputConfig;
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class UPathFollowingComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(abstract)
class AWarLegendPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AWarLegendPlayerController();
	
	void ChangeCity();
	void ChangeBattle();
	
	void ChangeLocation(const FVector& InVector);

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
	void OnInputStarted();
	void OnInventoryOpen();
	void OnEscClicked();
	
#pragma region Battle
	void OnBattleMove(const FInputActionValue& InActionValue);
	void OnBattleLook(const FInputActionValue& InActionValue);
#pragma endregion
	
	void MoveOnceToCachedDestination();
	
	bool IsUpdateCachedDestination();
	
private:
	void Init();
	
	void ShowTitle() const;
	void SetMouseState();
	
	void MoveToClickOrCloset(const FVector& InClickLocation);
	bool IsReachableLocation(const FVector& InClickLocation, FVector& OutLocation) const;
	
protected:
	// 네비메쉬용
	UPROPERTY(VisibleDefaultsOnly, Category = AI)
	TObjectPtr<UPathFollowingComponent> PathFollowingComponent;
	
	UPROPERTY(EditAnywhere, Category="Input")
	float ShortPressThreshold;
	
	// 커서이펙트
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UNiagaraSystem> FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SetDestinationClickAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SetInventoryAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SetEscClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SetDestinationTouchAction;
	
	// 배틀 인풋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Battle", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBattleInputConfig> InputBattleDataAsset;

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	/** Set to true if we're using touch input */
	uint32 bIsTouch : 1;

	/** Saved location of the character movement destination */
	FVector CachedDestination;

	/** Time that the click input has been pressed */
	float FollowTime = 0.0f;
};


