// Fill out your copyright notice in the Description page of Project Settings.


#include "UMyButton.h"

UUMyButton::UUMyButton(const FObjectInitializer& ObjectInitializer)
{
	InitIsFocusable(false);
}

void UUMyButton::RegActionBase()
{
	OnClicked.AddDynamic(this, &UUMyButton::OnClickBase);
	// OnPressed.AddDynamic(this, &UUMyButton::OnPressedBase);
	// OnReleased.AddDynamic(this, &UUMyButton::OnReleaseBase);
	// OnHovered.AddDynamic(this, &UUMyButton::OnHoverBase);
	// OnUnhovered.AddDynamic(this, &UUMyButton::OnUnhoverBase);
	//OnButtonDragEnter.add(this, &UUMyButton::OnDragEnterBase);
	//OnButtonDragDetected.BindLambda(this, &UUMyButton::OnDragBase);
	//OnButtonDragLeave.BindLambda(this, &UUMyButton::OnDragLeaveBase);
}

void UUMyButton::OnClickBase()
{
	if (OnClickWithNamed.IsBound())
	{
		OnClickWithNamed.Broadcast(GetFName());
	}
}

// void UUMyButton::OnPressedBase()
// {
// 	if (OnPressedWithNamed.IsBound())
// 	{
// 		OnPressedWithNamed.Broadcast(GetFName());
// 	}
// }
//
// void UUMyButton::OnReleaseBase()
// {
// 	if (OnReleaseWithNamed.IsBound())
// 	{
// 		OnReleaseWithNamed.Broadcast(GetFName());
// 	}
// }
//
// void UUMyButton::OnHoverBase()
// {
// 	if (OnHoverWithNamed.IsBound())
// 	{
// 		OnHoverWithNamed.Broadcast(GetFName());
// 	}
// }
//
// void UUMyButton::OnUnhoverBase()
// {
// 	if (OnUnhoverWithNamed.IsBound())
// 	{
// 		OnUnhoverWithNamed.Broadcast(GetFName());
// 	}
// }

// void UUMyButton::OnDragEnterBase(FGeometry& MyGeometry, FPointerEvent& MouseEvent)
// {
// 	if (OnDragEnterWithNamed.IsBound())
// 	{
// 		OnDragEnterWithNamed.Broadcast(GetFName());
// 	}
// }
//
// void UUMyButton::OnDragBase(FGeometry& MyGeometry, FPointerEvent& MouseEvent)
// {
// 	if (OnDragWithNamed.IsBound())
// 	{
// 		OnDragWithNamed.Broadcast(GetFName(), MyGeometry, MouseEvent);
// 	}
// }
//
// void UUMyButton::OnDragLeaveBase(FPointerEvent& MouseEvent)
// {
// 	if (OnDragLeaveWithNamed.IsBound())
// 	{
// 		OnDragLeaveWithNamed.Broadcast(GetFName());
// 	}
// }
