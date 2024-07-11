// Fill out your copyright notice in the Description page of Project Settings.


#include "RCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

#include "RInteractionComponent.h"
#include "RAttributeComponent.h"

// Sets default values
ARCharacter::ARCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<URInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<URAttributeComponent>("AttributeComp");

	SpawnProjectileDelay = 0.2f;
}

void ARCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ARCharacter::OnHealthChange);
}

// Called when the game starts or when spawned
void ARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = GetController<APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	
	//check(Subsystem);

	Subsystem->AddMappingContext(DefaultInputMapping, 0);

	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	InputComp->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARCharacter::Move);
	InputComp->BindAction(Input_LookMouse, ETriggerEvent::Triggered, this, &ARCharacter::Look);
	InputComp->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &ARCharacter::PrimaryAttack);
	InputComp->BindAction(Input_BlackHoleAttack, ETriggerEvent::Triggered, this, &ARCharacter::BlackHoleAttack);
	InputComp->BindAction(Input_Dash, ETriggerEvent::Triggered, this, &ARCharacter::Dash);
	InputComp->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	InputComp->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ARCharacter::Interact);
}

void ARCharacter::Move(const FInputActionInstance & Instance)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// Get value from input (combined value from WASD keys or single Gamepad stick) and convert to Vector (x,y)
	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();

	// Move forward/back
	AddMovementInput(ControlRot.Vector(), AxisValue.Y);

	// Move Right/Left strafe
	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, AxisValue.X);
}

void ARCharacter::Look(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void ARCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ARCharacter::PrimaryAttack_TimeElapsed, SpawnProjectileDelay);
}

void ARCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(PrimaryAttackProjectileClass);
}

void ARCharacter::BlackHoleAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_BlackHoleAttack, this, &ARCharacter::BlackHoleAttack_TimeElapsed, SpawnProjectileDelay);
}

void ARCharacter::BlackHoleAttack_TimeElapsed()
{
	SpawnProjectile(BlackHoleAttackProjectileClass);
}

void ARCharacter::Dash()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ARCharacter::Dash_TimeElapsed, SpawnProjectileDelay);
}

void ARCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void ARCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensure(ClassToSpawn))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, GetMesh(), "Muzzle_01");

		FHitResult Hit;

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = TraceStart + (GetControlRotation().Vector() * 5000);

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		// Sweep require less precision from player than line trace
		GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, Shape, CollisionParams);

		if (Hit.bBlockingHit)
			TraceEnd = Hit.ImpactPoint;

		FRotator DesiredRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(DesiredRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);

	}
}

void ARCharacter::Interact()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ARCharacter::OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// Player Damaged
	if (Delta < 0.f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("HitTime", GetWorld()->GetTimeSeconds());
	}

	// Player Death
	if (NewHealth <= 0.f && Delta < 0.f)
	{
		APlayerController* PC = GetController<APlayerController>();
		//APlayerController* PC = Cast<APlayerController>(GetController());
		// #include "Kismet/GameplayStatics.h"
		//APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		DisableInput(PC);
	}
}
