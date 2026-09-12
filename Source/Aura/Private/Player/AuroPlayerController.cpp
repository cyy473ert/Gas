// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuroPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



AAuroPlayerController::AAuroPlayerController()
{
	bReplicates = true;
}

void AAuroPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	//本地玩家的增强输入管理对象。
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuroPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent * EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuroPlayerController::Move);
}

void AAuroPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVctor= InputActionValue.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0,  Rotation.Yaw,0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);	
	if (APawn* ControlPawn = GetPawn<APawn>())
	{
		ControlPawn->AddMovementInput(ForwardDirection, InputAxisVctor.Y);
		ControlPawn->AddMovementInput(RightDirection, InputAxisVctor.X);
	}
}
