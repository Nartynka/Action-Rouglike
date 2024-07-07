// Fill out your copyright notice in the Description page of Project Settings.


#include "RPickup.h"

// Sets default values
ARPickup::ARPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	
	CooldownAmount = 10.f;
}

// Called when the game starts or when spawned
void ARPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPickup::Activate()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void ARPickup::Deactivate()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ARPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	TimerHandle_Reactive.Invalidate();
}

void ARPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	GetWorldTimerManager().SetTimer(TimerHandle_Reactive, this, &ARPickup::Activate, CooldownAmount);
	Deactivate();
}




// Called every frame
void ARPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

