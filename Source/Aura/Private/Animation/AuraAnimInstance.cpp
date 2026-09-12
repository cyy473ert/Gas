// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AuraAnimInstance.h"
#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UAuraAnimInstance::UAuraAnimInstance()
{
}

void UAuraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	AuraCharacter = Cast<AAuraCharacter>(TryGetPawnOwner());
	if (AuraCharacter)
	{
		CharacterMovement = AuraCharacter->GetCharacterMovement();
	}
}

void UAuraAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
	if (CharacterMovement)
	{
		AuraSpeed = CharacterMovement->Velocity.Size2D();
		if (AuraSpeed > 1)
		{
			bMove = true;
		}
		else
		{
			bMove = false;
		}
	}
}
