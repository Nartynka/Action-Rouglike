// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPickup.h"

#include "RHealthPotion.generated.h"


UCLASS()
class ACTIONROGUELIKE_API ARHealthPotion : public ARPickup
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARHealthPotion();

protected:

	UPROPERTY(EditAnywhere, Category = "Amounts")
	float HealthAmount;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Interact_Implementation(APawn* InstigatorPawn) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
