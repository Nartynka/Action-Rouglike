// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/RPickup_HealthPotion.h"
#include "RAttributeComponent.h"

// Sets default values
ARPickup_HealthPotion::ARPickup_HealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthAmount = 50.f;
}

// Called when the game starts or when spawned
void ARPickup_HealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPickup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	URAttributeComponent* AttributeComp = Cast<URAttributeComponent>(InstigatorPawn->GetComponentByClass(URAttributeComponent::StaticClass()));
	if (ensure(AttributeComp))
	{
		if (AttributeComp->IsMaxHealth())
			return;

		AttributeComp->ApplyHealthChange(this, HealthAmount);
		HideAndCooldownPicup();
	}
}
