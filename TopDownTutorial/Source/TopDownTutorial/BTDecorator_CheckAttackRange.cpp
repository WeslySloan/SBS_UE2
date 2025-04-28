// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckAttackRange.h"
#include "MyPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckAttackRange::UBTDecorator_CheckAttackRange()
{
	NodeName = TEXT("Check Attack Range");
}

bool UBTDecorator_CheckAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
		return false;

	auto Target = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	if (Target == nullptr)
		return false;

	if (Target->GetDistanceTo(Pawn) > 200.f)
		return false;

	return Result;
}
