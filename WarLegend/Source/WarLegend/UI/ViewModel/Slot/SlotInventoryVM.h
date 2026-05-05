#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "ETC/Struct.h"
#include "SlotInventoryVM.generated.h"

UCLASS()
class WARLEGEND_API USlotInventoryVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
	void SetData(const FMyItem& InData);
	void OnOpenItemInfo(const FMyItem& InData);
	
	const FMyItem& GetMyItem() { return MyItem; }

private:
	FMyItem MyItem;
};
