// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RGameplayInterface.h"

#include "RPickup.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ARPickup : public AActor, public IRGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPickup();

protected:

	FTimerHandle TimerHandle_Reactive;

	UPROPERTY(EditAnywhere, Category = "Amounts")
	float CooldownAmount;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void Interact_Implementation(APawn* InstigatorPawn);

	void Activate();
	void Deactivate();



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
