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

void ARAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIC = GetController<AAIController>();

	if (AIC)
	{
		UBlackboardComponent* Blackboard = AIC->GetBlackboardComponent();

		Blackboard->SetValueAsObject("TargetActor", Pawn);
		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}

void ARAICharacter::OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// Damage not healed
	if (Delta < 0.f)
	{
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

// Called every frame
void ARAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
