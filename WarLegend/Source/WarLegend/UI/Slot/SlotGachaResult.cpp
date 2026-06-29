#include "SlotGachaResult.h"

#include "Components/TextBlock.h"
#include "ETC/Define.h"
#include "ViewModel/Slot/SlotGachaResultVM.h"

void USlotGachaResult::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	VM = Cast<USlotGachaResultVM>(ListItemObject);
	VALID_RETURN(VM);
	
	SetData();
	ScheduleReveal();
}

void USlotGachaResult::NativeDestruct()
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(RevealTimerHandle);
	}

	Super::NativeDestruct();
}

void USlotGachaResult::SetData()
{
	RefreshGrade();
	RefreshItemName();
}

void USlotGachaResult::RefreshGrade()
{
	const FString ItemGradeName = VM->GetData().ItemGradeName;
	const FLinearColor ItemGradeColor = VM->GetData().GradeColor;
	
	Txt_Grade->SetText(FText::FromString(ItemGradeName));
	Txt_Grade->SetColorAndOpacity(ItemGradeColor);
}

void USlotGachaResult::RefreshItemName()
{
	const FString ItemName = VM->GetData().ItemName;
	const FLinearColor ItemGradeColor = VM->GetData().GradeColor;
	
	Txt_ItemName->SetText(FText::FromString(ItemName));
	Txt_ItemName->SetColorAndOpacity(ItemGradeColor);
}

void USlotGachaResult::ScheduleReveal()
{
	VALID_RETURN(VM);

	// 연출 전까지는 숨겨둔다.
	SetRenderOpacity(0.f);

	UWorld* World = GetWorld();
	VALID_RETURN(World);

	const float Delay = VM->GetRevealOrder() * RevealInterval;
	if (Delay <= 0.f)
	{
		PlayReveal();
		return;
	}

	World->GetTimerManager().SetTimer(RevealTimerHandle, this, &USlotGachaResult::PlayReveal, Delay, false);
}

void USlotGachaResult::PlayReveal()
{
	// 애니메이션이 없을 때도 보이도록 기본값 복구.
	SetRenderOpacity(1.f);

	// TODO: 등장 연출. UMG에 "Anim_Reveal" 애니메이션을 만들어두면 여기서 재생된다.
	if (Anim_Reveal)
	{
		PlayAnimation(Anim_Reveal);
	}
}
