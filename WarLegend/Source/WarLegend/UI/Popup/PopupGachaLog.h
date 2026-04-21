#pragma once

#include "CoreMinimal.h"
#include "Core/PopupWidgetBase.h"
#include "PopupGachaLog.generated.h"

struct FGachaLogData;
class UPopupGachaLogVM;
class UScrollBox;

UCLASS()
class WARLEGEND_API UPopupGachaLog : public UPopupWidgetBase
{
	GENERATED_BODY()

public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	virtual void BindViewModel() override;

private:
	void BindVM();
	void UnbindVM();

	void RebuildLogs();
	void CreateLogSlot(const FGachaLogData& InData);

	void HandleLogAdded(const FGachaLogData& InData);
	void HandleLogCleared();

private:
	UPROPERTY()
	TObjectPtr<UPopupGachaLogVM> VM;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> SB_Log;
};

