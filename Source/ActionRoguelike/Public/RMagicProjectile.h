// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RProjectileBase.h"

#include "RMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARMagicProjectile : public ARProjectileBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComp;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	

	ARMagicProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
