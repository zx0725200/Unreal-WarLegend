// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WarLegendBaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UEnemyAbilityConfig;
class UEnemyCombatComponent;
class UPawnCombatComponentBase;
class UHitFlashComponent;
class UWidgetComponent;

UCLASS()
class WARLEGEND_API AEnemyCharacter : public AWarLegendBaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(1); }
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent;}

	// 락온 마커(보스 위 이미지) 표시/숨김. LockOnComponent 가 호출.
	void SetLockOnMarkerVisible(bool bVisible);
	
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

	// 락온 마커 위젯(스크린 스페이스). 위젯 클래스/위치는 적 BP 에서 지정.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LockOn")
	TObjectPtr<UWidgetComponent> LockOnWidget;

};
