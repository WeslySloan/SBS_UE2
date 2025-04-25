// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterInfo.h"

// Sets default values for this component's properties
UCharacterInfo::UCharacterInfo()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UCharacterInfo::BeginPlay()
{
	Super::BeginPlay();

	Hp = MaxHp;
	
}

void UCharacterInfo::UpdateHp(float DamageAmount)
{
	Hp = FMath::Clamp(Hp - (int)DamageAmount, 0, MaxHp);

	OnHpChanaged.Broadcast();

	if (Hp == 0)
	{
		Status = ECharacterStatue::DEATH;
	}
}

float UCharacterInfo::GetHpRatio()
{
	if (MaxHp == 0 || Hp == 0)
		return 0.0f;

	return (float)Hp / (float)MaxHp;
}
