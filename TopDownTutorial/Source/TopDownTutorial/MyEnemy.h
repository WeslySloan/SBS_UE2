// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "MyEnemy.generated.h"

UCLASS()
class TOPDOWNTUTORIAL_API AMyEnemy : public AMyCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;



public:
	// Sets default values for this character's properties
	AMyEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	void OnDead(AActor* DamageCauser);

public:
	void Highlight();
	void UnHighlight();

};
