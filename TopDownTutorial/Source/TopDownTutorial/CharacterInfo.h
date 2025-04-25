// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterInfo.generated.h"

UENUM(BlueprintType)
enum class ECharacterStatue : uint8
{
	NONE,
	MOVING,
	ATTACK,
	DEATH,
};

DECLARE_MULTICAST_DELEGATE(FOnHpChanaged)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNTUTORIAL_API UCharacterInfo : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterStatue Status = ECharacterStatue::NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hp = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp = 100;
public:
	FOnHpChanaged OnHpChanaged;

public:	
	// Sets default values for this component's properties
	UCharacterInfo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

public:
	void UpdateHp(float DamageAmount);
	float GetHpRatio();
};
