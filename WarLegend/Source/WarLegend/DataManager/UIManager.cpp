#include "UIManager.h"
#include "UIManagerImpl.h"

void UIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	MgrImpl = NewObject<UUIManagerImpl>(this);
	if (MgrImpl)
	{
		MgrImpl->Initialize();
	}
}

void UIManager::Deinitialize()
{
	Super::Deinitialize();
	
	if (MgrImpl)
	{
		MgrImpl->Deinitialize();
	}
}
