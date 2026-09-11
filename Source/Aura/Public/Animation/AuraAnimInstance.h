// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/AuraCharacter.h"
#include "AuraAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
	
protected:
	UPROPERTY()
	TObjectPtr<AAuraCharacter> AuraCharacter;
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharacterMovement;
	UPROPERTY(BlueprintReadOnly,Category="AuraSpeed")
	float AuraSpeed;
};
