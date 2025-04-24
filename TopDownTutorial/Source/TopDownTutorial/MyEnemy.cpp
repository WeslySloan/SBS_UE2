// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "HpBarUserWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	AIControllerClass = AEnemyAIController::StaticClass();

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UHpBarUserWidget> UW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 20.f));
		HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));


	}


}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMyEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Log, TEXT("Damaged : %f"), Damage);
	return 0.0f;
}

void AMyEnemy::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
}

void AMyEnemy::UnHighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

