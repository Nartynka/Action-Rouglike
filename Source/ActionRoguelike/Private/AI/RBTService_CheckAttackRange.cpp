// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RBTService_CheckAttackRange.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


void URBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	// Check distance between AI Pawn and TargetActor

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (ensure(Blackboard))
	{
		AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject("TargetActor"));

		if (TargetActor)
		{
			AAIController* AIController = OwnerComp.GetAIOwner();
			if (ensure(AIController))
			{
				APawn* AIPawn = AIController->GetPawn();
				float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

				bool bWithinRange = DistanceTo < 2000.f;

				bool bHasLOS = false;
				if (bWithinRange)
				{
					bHasLOS = AIController->LineOfSightTo(TargetActor);
				}

				Blackboard->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLOS));

			}
		}
	}
}
