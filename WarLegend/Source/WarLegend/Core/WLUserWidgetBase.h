#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WLUserWidgetBase.generated.h"

/**
 * UI 코드의 기반이 되는 베이스 위젯입니다.
 */

UCLASS()
class WARLEGEND_API UWLUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Awake();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnDestroy();
	virtual void Update(const float InDeltaTime);
	
	UFUNCTION()
	virtual void OnClickEvent(const FName& InChildName);
	
	UFUNCTION()
	virtual void Show(const ESlateVisibility InVisible = ESlateVisibility::Visible);
	
	UFUNCTION()
	virtual void Hide(const ESlateVisibility InVisible = ESlateVisibility::Collapsed);
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
private:
	void InitChildWidget(TArray<UWidget*>& Children);
	
};
