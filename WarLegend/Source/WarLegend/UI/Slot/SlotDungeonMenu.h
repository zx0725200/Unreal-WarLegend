#pragma once

#include "CoreMinimal.h"
#include "Core/SlotWidgetBase.h"
#include "SlotDungeonMenu.generated.h"

class USlotDungeonVM;
class UTextBlock;
/**
 * 
 */
UCLASS()
class WARLEGEND_API USlotDungeonMenu : public USlotWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnClickEvent(const FName& InChildName) override;
	
	void SetData(USlotDungeonVM* InData);
	
private:
	void RefreshName(const FString& InName) const;
	void RefreshLevel(const int32 InMin, const int32 InMax) const;
	
private:
	UPROPERTY()
	TObjectPtr<USlotDungeonVM> VM;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Name;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Level;
};
