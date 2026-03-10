// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETC/Enum.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GachaManager.generated.h"

/**
 * 뽑기 확률 및 결과 처리
 * Normal  50%
 * Rare    30%
 * Unique  12%
 * Legend   5%
 * Epic     3%
 */

USTRUCT()
struct FGachaGradeWeight
{
	GENERATED_BODY()

	EItemGrade Grade = EItemGrade::None;
	float Weight = 0.f; // 가중치 (합산 후 정규화)
};

UCLASS()
class WARLEGEND_API UGachaManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:	
	int32 GetGachaItem() const;
	TArray<int32> GetGachaItemMultiple(const int32 InCount) const;

private:
	EItemGrade GetSelectedGrade() const;
	int32 GetSelectedItemByGrade(EItemGrade InGrade) const;

private:
	UPROPERTY()
	TArray<FGachaGradeWeight> GradeWeightTable; // 등급별 가중치 테이블
	TMap<EItemGrade, TArray<int32>> GradeToItemIDs; // 등급별 아이템 ID 캐시 (TableManager에서 구축)

	float TotalWeight = 0.f;
};
