// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"

#include "RCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class URInteractionComponent;
class UAnimMontage;
class UInputMappingContext;
class URAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ARCharacter : public ACharacter
{
	GENERATED_BODY()
 
protected:

	/* Read Only */
	UPROPERTY(VisibleAnywhere, Category = "_Effects")
	FName HandSocketName;

	UPROPERTY(VisibleAnywhere, Category = "_Effects")
	FName HitTimeParamName;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> PrimaryAttackProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleAttackProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* CastingEffect;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float SpawnProjectileDelay;


	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_BlackHoleAttack;
	FTimerHandle TimerHandle_Dash;

	/* COMPONENTS */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URAttributeComponent* AttributeComp;

	/* INPUT MAPPING */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_Move;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_LookMouse;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_PrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_BlackHoleAttack;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_Dash;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_Interact;

	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionValue& InputValue);

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();

	void BlackHoleAttack();
	void BlackHoleAttack_TimeElapsed();

	void Dash();
	void Dash_TimeElapsed();

	void StartAttackEffects();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);


	void Interact();

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

public:	

	// Sets default values for this character's properties
	ARCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
