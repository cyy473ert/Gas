// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuroPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/EnemyInterface.h"


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

void AAuroPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CursorTrace();
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

void AAuroPlayerController::CursorTrace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,Hit);
	if (Hit.bBlockingHit) return;
	LastCursor = ThisCursor;
	ThisCursor = Cast<IEnemyInterface>(Hit.GetActor()); //这是的判断是判断这个actor有没有实现这个接口
	/*1.last 空 this 空    nothing
	 *2.last 空 this 有    CursorOn()
	 *3.last 有 this 空    UnCursorOn() 
	 *4.last 有 this 有但是和上一个是不同的    last UnCursorOn()  this CursorOn()
	 *5.last 空 this 空    nothing
	 */
	if (LastCursor == nullptr)
	{
		if (ThisCursor)
		{
			ThisCursor->CursorOn();
		}
	}
	else
	{
		if (ThisCursor == nullptr)
		{
			LastCursor->UnCursorOn();
		}
		else if(ThisCursor == nullptr && LastCursor != ThisCursor) 
		{
			LastCursor->UnCursorOn();
			ThisCursor->CursorOn();
		}
	}
}
