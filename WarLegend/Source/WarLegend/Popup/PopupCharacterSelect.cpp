#include "PopupCharacterSelect.h"

#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "ETC/Define.h"

void UPopupCharacterSelect::OnEnable()
{
	Super::OnEnable();
}

void UPopupCharacterSelect::OnDisable()
{
	Super::OnDisable();
}

void UPopupCharacterSelect::OnClickEvent(const FName& InChildName)
{
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Confirm"))
	{
		OnClickedConfirm();
	}
}

void UPopupCharacterSelect::OnClickedConfirm()
{
	Hide();
	
	if (const auto UIMgr = GTUIGetMgrImpl(UIManager))
	{
		UIMgr->ShowUI(TEXT("HudPlayerState"));
	}
}
