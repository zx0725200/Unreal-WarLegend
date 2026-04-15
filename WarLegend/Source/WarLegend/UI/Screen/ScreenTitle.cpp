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
	Super::OnClickEvent(InChildName);
	
	if (InChildName == TEXT("Btn_Confirm"))
	{
		OnClickedConfirm();
	}
}

void UScreenTitle::BindViewModel()
{
	Super::BindViewModel();
	
	auto* TitleVM = NewObject<UScreenTitleVM>(this);
	TitleVM->Init();
	
	SetViewModel(TitleVM);
}

void UScreenTitle::SetViewModel(UScreenTitleVM* InViewModel)
{
	VM = InViewModel;
}

void UScreenTitle::OnClickedConfirm()
{
	Hide();
	
	VALID_RETURN(VM);
	VM->OnConfirm();
}
