// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "EnemyAIController.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AMyEnemy::AMyEnemy()
{
	AIControllerClass = AEnemyAIController::StaticClass();

}

void AMyEnemy::ApplyDamage(AActor* Actor)
{
	auto Player = Cast<AMyPlayer>(Actor);
	if (Player)
	{
		UGameplayStatics::ApplyDamage(Player, 10.f, GetController(), nullptr, NULL);
	}

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

