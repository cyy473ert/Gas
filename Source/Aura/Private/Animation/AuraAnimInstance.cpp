// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AuraAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"

UAuraAnimInstance::UAuraAnimInstance()
{
}

void UAuraAnimInstance::NativeInitializeAnimation()
{
	if (AuraCharacter != nullptr)
	{
		CharacterMovement = AuraCharacter->GetCharacterMovement();
	}
}

void UAuraAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
	if (CharacterMovement != nullptr)
	{
		AuraSpeed = CharacterMovement->Velocity.Size2D();
	}
}
