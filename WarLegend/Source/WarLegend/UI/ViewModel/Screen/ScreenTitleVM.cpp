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
	
	UIMgr->ShowUI(TEXT("HudBossHp"), ESlateVisibility::SelfHitTestInvisible);
	UIMgr->ShowUI(TEXT("HudMain"), ESlateVisibility::SelfHitTestInvisible);
}
