#include "ScreenTitle.h"
#include "ViewModel/Screen/ScreenTitleVM.h"

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
	VALID_RETURN(VM);
	
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Confirm"))
	{
		VM->OnConfirm();
		Hide();
	}
}

void UScreenTitle::BindViewModel()
{
	Super::BindViewModel();
	
	VM = NewObject<UScreenTitleVM>(this);
	VM->Init();
}
