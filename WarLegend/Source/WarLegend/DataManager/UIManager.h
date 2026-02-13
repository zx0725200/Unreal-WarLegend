#pragma once
#include "CoreMinimal.h"
#include "UIManager.generated.h"

class UUIManagerImpl;

UCLASS()
class UIManager : public ULocalPlayerSubsystem 
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UPROPERTY(BlueprintReadOnly)
	UUIManagerImpl* MgrImpl = nullptr;
};
