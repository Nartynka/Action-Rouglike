


#include "RInteractionComponent.h"
#include "RGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
URInteractionComponent::URInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void URInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	//FHitResult Hit;
	//GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	
	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	Shape.SetSphere(30.f);

	// Sweep is more user friendly because they don't have to point with 1px line but have a range in shape of sphere
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (FHitResult& Hit : Hits)
	{
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.f, 32, LineColor, false, 2.f);
		if (AActor* HitActor = Hit.GetActor())
		{
			
			if (HitActor->Implements<URGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IRGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}

	}

	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 2.f);
}


