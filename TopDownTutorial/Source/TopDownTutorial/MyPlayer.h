// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

class UInputAction;

UCLASS()
class TOPDOWNTUTORIAL_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	UPROPERTY(VisibleAnywhere)
	bool bIsAttacking = false;
	UPROPERTY()
	class UCharacterAnimInstance* AnimInstance;		   
public:
	AMyPlayer();
public:
	void Attack();	  
	void HitAttack();	// Ãß°¡


	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
