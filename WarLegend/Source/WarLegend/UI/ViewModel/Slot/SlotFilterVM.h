// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "UObject/Object.h"
#include "SlotFilterVM.generated.h"

enum class EItemGrade : uint8;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFilterChanged, EItemGrade, bool);

/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotFilterVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	void Init(const EItemGrade InGrade, const FString& InName, const FLinearColor& InColor, const bool InChecked);
	void SetChecked(bool InChecked);
	void OnFilterChanged(const EItemGrade InGrade, const bool InChecked);
	
	EItemGrade			GetGrade() const { return Grade; }
	FString				GetGradeName() const { return GradeName; }
	FLinearColor		GetGradeColor() const { return GradeColor; }
	bool				IsChecked() const { return bChecked; }
	
private:
	EItemGrade Grade;
	FString GradeName = TEXT("");
	FLinearColor GradeColor;
	bool bChecked = true;
};
