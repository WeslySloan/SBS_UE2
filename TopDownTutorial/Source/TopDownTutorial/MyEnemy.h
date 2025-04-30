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
public:
	virtual void ApplyDamage(AActor* Actor) override;
public:
	void Highlight();
	void UnHighlight();

};
