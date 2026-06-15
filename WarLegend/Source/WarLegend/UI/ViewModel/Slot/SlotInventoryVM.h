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

	// HP+ATK+DEF 합이 같은 타입 장착템보다 높으면 true (업그레이드 화살표 표시용)
	bool IsUpgrade() const;

private:
	FMyItem MyItem;
};
