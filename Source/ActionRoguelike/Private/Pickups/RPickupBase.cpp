// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/RPickupBase.h"

// Sets default values
ARPickupBase::ARPickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	
	CooldownAmount = 10.f;
}

// Called when the game starts or when spawned
void ARPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPickupBase::Interact_Implementation(APawn* InstigatorPawn)
{
	// Implementation in derived class
}

void ARPickupBase::SetPickupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	RootComponent->SetVisibility(bNewIsActive, true);
}

void ARPickupBase::ShowPickup()
{
	SetPickupState(true);
}

void ARPickupBase::HideAndCooldownPicup()
{
	SetPickupState(false);
	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &ARPickupBase::ShowPickup, CooldownAmount);
}

void ARPickupBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	TimerHandle_Respawn.Invalidate();
}