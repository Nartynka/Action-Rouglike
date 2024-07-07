// Fill out your copyright notice in the Description page of Project Settings.


#include "RHealthPotion.h"
#include "RAttributeComponent.h"

// Sets default values
ARHealthPotion::ARHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthAmount = 50.f;
}

// Called when the game starts or when spawned
void ARHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	URAttributeComponent* AttributeComp = Cast<URAttributeComponent>(InstigatorPawn->GetComponentByClass(URAttributeComponent::StaticClass()));
	if (AttributeComp)
	{
		if (AttributeComp->IsMaxHealth())
			return;

		AttributeComp->ApplyHealthChange(this, HealthAmount);
		GetWorldTimerManager().SetTimer(TimerHandle_Reactive, this, &ARHealthPotion::Activate, CooldownAmount);
		Deactivate();
	}
}

// Called every frame
void ARHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

