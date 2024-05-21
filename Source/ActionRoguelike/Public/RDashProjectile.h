// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileBase.h"
#include "RDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ARDashProjectile : public ARProjectileBase
{
	GENERATED_BODY()
public:
	ARDashProjectile();

protected:

	FTimerHandle TimerHandle_DelayedExplode;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float ExplodeDelay = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay = 0.2f;

	void BeginPlay() override;
	void Explode() override;

	void TeleportInstigator();

};
