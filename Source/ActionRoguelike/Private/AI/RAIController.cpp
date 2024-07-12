// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/RAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ARAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree is nullptr! Please assign Behavior Tree in your AI Controller.")))
	{
		RunBehaviorTree(BehaviorTree);
	}

}
