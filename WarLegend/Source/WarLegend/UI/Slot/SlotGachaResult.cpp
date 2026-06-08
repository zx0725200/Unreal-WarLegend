// Fill out your copyright notice in the Description page of Project Settings.


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

void USlotGachaResult::SetData() const
{
	VALID_RETURN(VM);

	const FGachaLogData& Data = VM->GetData();

	Txt_Grade->SetText(FText::FromString(Data.ItemGradeName));
	Txt_Grade->SetColorAndOpacity(Data.GradeColor);

	Txt_ItemName->SetText(FText::FromString(Data.ItemName));
	Txt_ItemName->SetColorAndOpacity(Data.GradeColor);
}

void USlotGachaResult::ScheduleReveal()
{
	VALID_RETURN(VM);

	// 연출 전까지는 숨겨둔다. (연출 애니메이션이 알파/스케일을 0에서 살려주는 형태라고 가정)
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
