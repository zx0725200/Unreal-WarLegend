// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WarLegendBaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UEnemyAbilityConfig;
class UEnemyCombatComponent;
class UPawnCombatComponentBase;
class UHitFlashComponent;

UCLASS()
class WARLEGEND_API AEnemyCharacter : public AWarLegendBaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(1); }
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent;}
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnCombatComponentBase* GetPawnCombatComponent() const override;

	
private:
	void Init();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	// 피격 시 메시 번쩍(데미지 피드백). FlashMaterial 은 적 BP 에서 지정.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UHitFlashComponent> HitFlashComponent;

};
