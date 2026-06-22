#include "PopupGacha.h"
#include "ETC/Constant.h"
#include "ETC/Define.h"
#include "ViewModel/Popup/PopupGachaVM.h"

void UPopupGacha::Awake()
{
	Super::Awake();
}

void UPopupGacha::OnEnable()
{
	Super::OnEnable();
}

void UPopupGacha::OnDisable()
{
	Super::OnDisable();
}

void UPopupGacha::OnClickEvent(const FName& InChildName)
{
	VALID_RETURN(VM);
	Super::OnClickEvent(InChildName);

	if (InChildName == TEXT("Btn_One"))
	{
		VM->OnGacha(Constant::One);
	}
	else if (InChildName == TEXT("Btn_Ten"))
	{
		VM->OnGacha(Constant::Ten);
	}
	else if (InChildName == TEXT("Btn_All"))
	{
		VM->OnGacha(Constant::All);
	}
}

void UPopupGacha::BindViewModel()
{
	Super::BindViewModel();

	VM = NewObject<UPopupGachaVM>(this);
	VM->Init();
}
