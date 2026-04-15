#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ETC/Define.h"
#include "Interface/IViewModelInterface.h"
#include "WLUserWidgetBase.generated.h"

/**
 * UI 코드의 기반이 되는 베이스 위젯입니다.
 */

class UScreenInventoryVM;

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
class WARLEGEND_API UWLUserWidgetBase : public UUserWidget, public IViewModelInterface
{
	GENERATED_BODY()
	
public:
	virtual void Awake();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnDestroy();
	virtual void Update(const float InDeltaTime);
	
	virtual void SetUIType(EUserWidgetType InType);
	virtual EUserWidgetType GetUIType() const { return WidgetType; }
	
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
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual void BindViewModel() override;
	
private:
	void InitChildWidget(TArray<UWidget*>& Children);
	
	void LockPlayerInput();
	void UnlockPlayerInput() const;

public:
	FWLUIEventHandle UIEventHandle;
	
private:
	EUserWidgetType WidgetType;
};
