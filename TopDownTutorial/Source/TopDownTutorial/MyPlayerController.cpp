// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "MyEnemy.h" 
#include "Kismet/KismetMathLibrary.h"




AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;

	
}

void AMyPlayerController::BeginPlay()
{

	Super::BeginPlay();

	MyPlayer = Cast<AMyPlayer>(GetPawn());


}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// SetDestinationClickAction
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AMyPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AMyPlayerController::OnSetDestinationReleased);
		

	}
}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CheckCursorTrace();
	FollowAndAttack();
}

void AMyPlayerController::OnInputStarted()
{
	StopMovement();

	bMousePressed = true;

	TargetActor = PointActor;
}

void AMyPlayerController::OnSetDestinationTriggered()
{
	if (TargetActor)
		return;

	FollowTime += GetWorld()->GetDeltaSeconds();

	FHitResult Hit;

	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	if (MyPlayer != nullptr)
	{
		FVector WorldDirection = (CachedDestination - MyPlayer->GetActorLocation()).GetSafeNormal();
		MyPlayer->AddMovementInput(WorldDirection, 1.0, false);

	}

}

void AMyPlayerController::OnSetDestinationReleased()
{
	bMousePressed = false;

	if (FollowTime <= ShortPressThreshold)
	{
		if (TargetActor == nullptr)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination);
		}

	}

	FollowTime = 0.f;
}

void AMyPlayerController::CheckCursorTrace()
{
	if (bMousePressed)
		return;

	FHitResult Hit;

	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit))
	{
		AMyEnemy* Other = Cast<AMyEnemy>(Hit.GetActor());
		if (Other == nullptr)
		{
			if (PointActor)
			{
				PointActor->UnHighlight();
			}

		}
		else
		{
			if (PointActor)
			{
				if (PointActor != Other)
				{
					PointActor->UnHighlight();
					Other->Highlight();
				}
			}
			else
			{
				Other->Highlight();
			}
		}

		PointActor = Other;
	}
}

void AMyPlayerController::FollowAndAttack()
{
	if (TargetActor == nullptr)
		return;

	FVector Direction = TargetActor->GetActorLocation() - MyPlayer->GetActorLocation();
	float Distance = Direction.Size2D();

	if (Distance < 250.f)
	{
		UE_LOG(LogTemp, Log, TEXT("Distance"));

		if (bMousePressed)
		{
			UE_LOG(LogTemp, Log, TEXT("bMousePressed"));
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(MyPlayer->GetActorLocation(), TargetActor->GetActorLocation());
			MyPlayer->SetActorRotation(LookAtRotation);

			if (AttackMontage)
			{
				UE_LOG(LogTemp, Log, TEXT("ATTACK"));
				GetCharacter()->PlayAnimMontage(AttackMontage);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Not Attack"));
			}

			TargetActor = PointActor;
		}
		else
		{
			TargetActor = nullptr;
		}

	}
	else
	{
		FVector WorldDirection = Direction.GetSafeNormal();
		MyPlayer->AddMovementInput(WorldDirection, 1.0, false);

	}

}

