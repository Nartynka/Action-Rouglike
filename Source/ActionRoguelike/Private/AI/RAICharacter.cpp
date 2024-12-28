// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RAICharacter.h"

#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"

#include "RAttributeComponent.h"

// Sets default values
ARAICharacter::ARAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeComp = CreateDefaultSubobject<URAttributeComponent>("AttributeComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ARAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ARAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &ARAICharacter::OnHealthChange);
}

void ARAICharacter::OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// Damage not healed
	if (Delta < 0.f)
	{
		// Check if the instigator is not ourself
		// Instigator can be the player or other AI
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		// Death
		if (NewHealth <= 0.0f)
		{
			// Stop BT
			AAIController* AIC = GetController<AAIController>();
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			SetLifeSpan(10.0f);
		}
	}
}

void ARAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = GetController<AAIController>();

	if (AIC)
	{
		// We don't check for null on blackboard comp because
		// Blackboard component will never be null if the controller is alive
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}

void ARAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}
