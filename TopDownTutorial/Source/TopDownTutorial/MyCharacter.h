// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TOPDOWNTUTORIAL_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()	

public:
	UPROPERTY(VisibleAnywhere)
	bool bIsAttacking = false;

	UPROPERTY(BlueprintReadOnly)
	class UWidgetComponent* HpBar;
	UPROPERTY()
	class UCharacterInfo* CharacterInfo;
	UPROPERTY()
	class UCharacterAnimInstance* AnimInstance;
public:
	AMyCharacter();
protected:
	virtual void BeginPlay() override;
public:
	void Attack();
	void HitAttack();
public:
	virtual void ApplyDamage(AActor* Actor);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnDead(AActor* DamageCauser);

};
