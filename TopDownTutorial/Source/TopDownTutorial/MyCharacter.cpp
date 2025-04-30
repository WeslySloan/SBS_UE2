// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "CharacterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "HpBarUserWidget.h"
#include "Components/WidgetComponent.h"
#include "CharacterInfo.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyCharacter::AMyCharacter()
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

	CharacterInfo = CreateDefaultSubobject<UCharacterInfo>(TEXT("CharacterInfo"));

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
	AnimInstance->OnAttackHit.AddUObject(this, &AMyCharacter::HitAttack);

	auto HpWidget = Cast<UHpBarUserWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(CharacterInfo);
	}
}

void AMyCharacter::Attack()
{
	if (bIsAttacking)
		return;

	AnimInstance->PlayAttackMontage();

	bIsAttacking = true;
}

void AMyCharacter::HitAttack()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 150.f;
	float AttackRadius = 50.f;

	bool Result = GetWorld()->SweepSingleByChannel(OUT HitResult,
		GetActorLocation(), GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	FVector Forward = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + Forward * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Forward).ToQuat();

	FColor DrawColor = Result ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);

	if (Result && HitResult.GetActor())
	{
		ApplyDamage(HitResult.GetActor());
	}
}

void AMyCharacter::ApplyDamage(AActor* Actor)
{
	UGameplayStatics::ApplyDamage(Actor, 10.f, GetController(), nullptr, NULL);
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CharacterInfo->UpdateHp(Damage);

	if (CharacterInfo->Status == ECharacterStatue::DEATH)
	{
		OnDead(DamageCauser);
	}

	return Damage;
}

void AMyCharacter::OnDead(AActor* DamageCauser)
{
	  //Todo
}
