#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WLUserWidgetBase.generated.h"

/**
 * UI 코드의 기반이 되는 베이스 위젯입니다.
 */

UENUM(Blueprintable)
enum class EUserWidgetType : uint8
{
	None,
	Slot,
	Hud,
	Popup,
	Screen,
};

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
	
	virtual EUserWidgetType GetUIType() const { return EUserWidgetType::Screen; }
	
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
	
	void LockPlayerInput() const;
	void UnlockPlayerInput() const;
	
};
