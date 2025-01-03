

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RGameplayInterface.h"

#include "RItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ARItemChest : public AActor, public IRGameplayInterface
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	// ! The "_Implementation" is not from the interface but from the UPROPERTY(BlueprintNativeEvent)
	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

public:	

	// Sets default values for this actor's properties
	ARItemChest();

};
