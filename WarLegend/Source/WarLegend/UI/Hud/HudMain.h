#pragma once

#include "CoreMinimal.h"
#include "Core/HudWidgetBase.h"
#include "HudMain.generated.h"

class UHudMainVM;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UHudMain : public UHudWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void BindViewModel() override;
	
private:
	UPROPERTY()
	TObjectPtr<UHudMainVM> VM;
};
