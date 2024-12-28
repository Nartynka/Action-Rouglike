// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/RMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

#include "RAttributeComponent.h"

// Sets default values
ARMagicProjectile::ARMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);

	InitialLifeSpan = 10.
}

void ARMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARMagicProjectile::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ARMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	AudioComp->Play();
}

// This triggers only for WorldDynamics and Pawns, the rest triggers OnHit event in base class
void ARMagicProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Projectile only overlaps WorldDynamics and Pawns
	// The rest is set to block, so the OnHit event in base class is triggered instead
	if (OtherActor && OtherActor != GetInstigator())
	{
		URAttributeComponent* AttributeComp = Cast<URAttributeComponent>(OtherActor->GetComponentByClass(URAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(), -Damage);
			//UGameplayStatics::PlayWorldCameraShake(this, )
			Explode();
		}
	}
}