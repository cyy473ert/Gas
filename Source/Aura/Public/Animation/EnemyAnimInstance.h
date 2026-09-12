// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

class AAuraEnemy;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class AURA_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UEnemyAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
	
protected:
	UPROPERTY()
	TObjectPtr<AAuraEnemy> EnemyCharacter;
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> EnemyMovement;
	UPROPERTY(BlueprintReadOnly,Category="AuraSpeed")
	float EnemySpeed;
	
};
