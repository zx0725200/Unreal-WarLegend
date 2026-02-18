#include "ScreenTitle.h"

#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "ETC/Define.h"

void UScreenTitle::OnEnable()
{
	Super::OnEnable();
}

void UScreenTitle::OnDisable()
{
	Super::OnDisable();
}

void UScreenTitle::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Confirm"))
	{
		OnClickedConfirm();
	}
}

void UScreenTitle::OnClickedConfirm()
{
	Hide();
	
	if (const auto UIMgr = GTUIGetMgrImpl(UIManager))
	{
		UIMgr->ShowUI(TEXT("HudPlayerState"));
	}
}
