// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "CharacterAnimInstance.h"
#include "Kismet/GameplayStatics.h"

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
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), 10.f, GetController(), nullptr, NULL);
	}
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
}
