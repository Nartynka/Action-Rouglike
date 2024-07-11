// Fill out your copyright notice in the Description page of Project Settings.


#include "RAttributeComponent.h"

// Sets default values for this component's properties
URAttributeComponent::URAttributeComponent()
{
	HealthMax = 100.f;
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
	Health = FMath::Clamp(Health + Delta, 0.f, HealthMax);
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

	return true;
}
