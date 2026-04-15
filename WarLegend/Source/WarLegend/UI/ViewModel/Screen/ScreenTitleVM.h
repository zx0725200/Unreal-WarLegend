// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ViewModelBase.h"
#include "ScreenTitleVM.generated.h"

UCLASS()
class WARLEGEND_API UScreenTitleVM : public UViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	void OnConfirm() const;
};
