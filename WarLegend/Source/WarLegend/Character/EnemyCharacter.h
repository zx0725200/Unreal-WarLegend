// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WarLegendBaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UPawnCombatComponentBase;

UCLASS()
class WARLEGEND_API AEnemyCharacter : public AWarLegendBaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent;}
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnCombatComponentBase* GetPawnCombatComponent() const override;
	
private:
	void Init();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;
	
};
