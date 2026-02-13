#pragma once

#include "CoreMinimal.h"
#include "Core/WLUserWidgetBase.h"
#include "PopupWidgetBase.generated.h"

/**
 * 팝업을 사용할 때 베이스가 되는 위젯입니다. 
 */

UCLASS()
class WARLEGEND_API UPopupWidgetBase : public UWLUserWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;
	virtual void Update(const float InDeltaTime) override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
private:
	
};
