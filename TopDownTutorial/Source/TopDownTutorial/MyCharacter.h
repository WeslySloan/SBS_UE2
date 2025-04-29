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
	void Attack();
	void HitAttack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

};
