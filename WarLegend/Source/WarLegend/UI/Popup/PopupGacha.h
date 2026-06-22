#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupGacha.generated.h"

class UPopupGachaVM;

UCLASS()
class WARLEGEND_API UPopupGacha : public UPopupWidgetBase
{
	GENERATED_BODY()

public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	virtual void BindViewModel() override;

private:
	UPROPERTY()
	TObjectPtr<UPopupGachaVM> VM;
};


