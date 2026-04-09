// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimLayer.h"

#include "CharacterAnimInstance.h"

UCharacterAnimInstance* UCharacterAnimLayer::GetCharacterAnimInstance()
{
	return Cast<UCharacterAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
