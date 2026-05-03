#include "ScreenTitleVM.h"
#include "UIManagerImpl.h"
#include "ETC/Define.h"

void UScreenTitleVM::Init()
{
	Super::Init();
}

void UScreenTitleVM::OnConfirm() const
{
	UUIManagerImpl* UIMgr = GetUIManager();
	VALID_RETURN(UIMgr);
	
	UIMgr->ShowUI(TEXT("HudMain"));
	UIMgr->ShowUI(TEXT("HudBossHp"));
}
