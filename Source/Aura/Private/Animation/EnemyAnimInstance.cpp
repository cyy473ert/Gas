// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	EnemyCharacter= Cast<AAuraEnemy>(TryGetPawnOwner());
	if (EnemyCharacter != nullptr)
	{
		EnemyMovement = EnemyCharacter->GetCharacterMovement();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
	if (EnemyMovement != nullptr)
	{
		EnemySpeed = EnemyMovement->Velocity.Size2D();
	}
}
