// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTargetDummy.generated.h"

class UStaticMeshComponent;
class URAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ARTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTargetDummy();

protected:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	URAttributeComponent* AttributeComp;

	UFUNCTION()
	void OnHealthChanged(float NewHealth, float Delta);
};
