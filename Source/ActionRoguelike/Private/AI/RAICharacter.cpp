// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RAICharacter.h"

#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "RAttributeComponent.h"

// Sets default values
ARAICharacter::ARAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributeComp = CreateDefaultSubobject<URAttributeComponent>("AttributeComp");

}

// Called when the game starts or when spawned
void ARAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents()	;

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ARAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &ARAICharacter::OnHealthChange);
}

void ARAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (AIC)
	{
		UBlackboardComponent* Blackboard = AIC->GetBlackboardComponent();

		Blackboard->SetValueAsObject("TargetActor", Pawn);
		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}

void ARAICharacter::OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// Death
	if (NewHealth <= 0.f && Delta < 0.f)
	{
		Destroy();
	}
}

// Called every frame
void ARAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
