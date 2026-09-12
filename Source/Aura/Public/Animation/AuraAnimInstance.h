// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AuraAnimInstance.generated.h"

class AAuraCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAuraAnimInstance();
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
	
protected:
	UPROPERTY(BlueprintReadWrite,Category="Aiminstance")
	TObjectPtr<AAuraCharacter> AuraCharacter;
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharacterMovement;
	UPROPERTY(BlueprintReadOnly,Category="Aiminstance")
	float AuraSpeed;
	UPROPERTY(BlueprintReadOnly,Category="Aiminstance")
	bool bMove = false;
};
