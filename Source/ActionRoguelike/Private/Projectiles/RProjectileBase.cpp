// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/RProjectileBase.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ARProjectileBase::ARProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	Damage = 20.f;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovmentComp");
	MovementComp->InitialSpeed = 4000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.f;
}

void ARProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ARProjectileBase::OnHit);
}

// Called when the game starts or when spawned
void ARProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

}


// Triggers for everything but WorldDynamics and Pawns
void ARProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ARProjectileBase::Explode_Implementation()
{
	// If we accidentally call explode twice
	if (ensure(IsValid(this)))
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplodeParticle, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}
