#include "UIFlowPresenter.h"

#include "GachaPresenter.h"

void UUIFlowPresenter::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUIFlowPresenter::OpenPopupGacha() const
{
	if (!GachaPresenter) return;
	
	GachaPresenter->OpenPopupGacha();
}

void UUIFlowPresenter::OpenPopupGachaFilter() const
{
	if (!GachaPresenter) return;
	
	GachaPresenter->OpenPopupGachaFilter();
}

void UUIFlowPresenter::OpenPopupGachaLog() const
{
	if (!GachaPresenter) return;
	
	GachaPresenter->OpenPopupGachaLog();
}
