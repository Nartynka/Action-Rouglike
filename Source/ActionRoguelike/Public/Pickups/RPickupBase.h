// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RGameplayInterface.h"

#include "RPickupBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ARPickupBase : public AActor, public IRGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPickupBase();

protected:

	FTimerHandle TimerHandle_Respawn;

	UPROPERTY(EditAnywhere, Category = "Amounts")
	float CooldownAmount;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void Interact_Implementation(APawn* InstigatorPawn);

	void ShowPickup();
	void HideAndCooldownPicup();

	void SetPickupState(bool bNewIsActive);
};
