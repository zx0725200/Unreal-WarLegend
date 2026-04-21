// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETC/Enum.h"
#include "ETC/Struct.h"
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

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGachaLogAdded, const FGachaLogData&);
DECLARE_MULTICAST_DELEGATE(FOnGachaLogCleared);

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

	void ApplyFilter();
	void AddLog(const int32 ItemID);
	void ClearLogs();
	
	int32 GetGachaItem() const;
	const TArray<FGachaLogData>& GetLogList() const { return LogList; }
	TArray<int32> GetGachaItemMultiple(const int32 InCount) const;

	FOnGachaLogAdded& GetOnLogAdded() { return OnLogAdded; }
	FOnGachaLogCleared& GetOnLogCleared() { return OnLogCleared; }

private:
	void BuildCache();
	void SetFilter(const TArray<EItemGrade>& InAllowedGrades);

	EItemGrade GetSelectedGrade() const;
	int32 GetSelectedItemByGrade(EItemGrade InGrade) const;
	float GetTotalWeight() const;

private:
	TArray<FGachaGradeWeight> GradeWeightTable;		// 등급별 가중치 테이블
	TArray<EItemGrade> FilterGrades;				// 필터 처리된 등급
	TArray<FGachaLogData> LogList;					// 뽑기 로그 리스트
	TMap<EItemGrade, TArray<int32>> GradeToItemIDs; // 등급별 아이템 ID 캐시
	
	FOnGachaLogAdded OnLogAdded;
	FOnGachaLogCleared OnLogCleared;
	
	float TotalWeight = 0.f;
};
