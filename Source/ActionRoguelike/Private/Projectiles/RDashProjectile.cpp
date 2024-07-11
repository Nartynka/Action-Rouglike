// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/RDashProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ARDashProjectile::ARDashProjectile()
{
	ExplodeDelay = 0.2f;
	TeleportDelay = 0.2f;

	MovementComp->InitialSpeed = 6000.f;
}

void ARDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedExplode, this, &ARDashProjectile::Explode, ExplodeDelay);
}


void ARDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedExplode);

	UGameplayStatics::SpawnEmitterAtLocation(this, ExplodeParticle, GetActorLocation(), GetActorRotation());
	
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ARDashProjectile::TeleportInstigator, TeleportDelay);
	
	EffectComp->DeactivateSystem();
	SetActorEnableCollision(false);

	// We have another delay so we must stop the projectile or we will teleport to different location
	MovementComp->StopMovementImmediately();
}

void ARDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();

	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	}

	Destroy();
}

