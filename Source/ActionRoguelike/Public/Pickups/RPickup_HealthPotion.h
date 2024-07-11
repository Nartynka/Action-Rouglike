// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/RPickupBase.h"

#include "RPickup_HealthPotion.generated.h"


UCLASS()
class ACTIONROGUELIKE_API ARPickup_HealthPotion : public ARPickupBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPickup_HealthPotion();

protected:

	UPROPERTY(EditAnywhere, Category = "Amounts")
	float HealthAmount;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void Interact_Implementation(APawn* InstigatorPawn) override;

};
