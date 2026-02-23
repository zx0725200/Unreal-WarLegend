#include "ScreenTitle.h"
#include "ViewModel/ScreenTitleVM.h"

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
	
	if (!VM)
	{
		return;
	}
	
	VM->Confirm();
}
