// Fill out your copyright notice in the Description page of Project Settings.


#include "RAttributeComponent.h"

// Sets default values for this component's properties
URAttributeComponent::URAttributeComponent()
{
	HealthMax = 100.0f;
	Health = HealthMax;
}

bool URAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool URAttributeComponent::IsMaxHealth() const
{
	return Health == HealthMax;
}

bool URAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return ActualDelta != 0;
}
