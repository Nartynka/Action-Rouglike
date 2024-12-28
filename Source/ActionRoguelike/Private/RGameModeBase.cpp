// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "AI/RAICharacter.h"
#include "EngineUtils.h"
#include "RAttributeComponent.h"


ARGameModeBase::ARGameModeBase()
{
	SpawnTimerInterval = 2.f;
}

void ARGameModeBase::StartPlay()
{
	Super::StartPlay();
	if (!bShouldSpawnBots)
	{
		UE_LOG(LogTemp, Warning, TEXT("bShouldSpawnBots is set to false. Skipping spawning bots!"));
		return;
	}

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ARGameModeBase::SpawnBots_TimeElapsed, SpawnTimerInterval, true);
}

void ARGameModeBase::SpawnBots_TimeElapsed()
{
	int32 NrOfAliveBots = 0;

	// Count alive bots
	for (TActorIterator<ARAICharacter> It(GetWorld()); It; ++It)
	{
		ARAICharacter* Bot = *It;
		URAttributeComponent* AttributeComp = Bot->GetComponentByClass<URAttributeComponent>();

		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("%i alive bots"), NrOfAliveBots);

	float MaxBotsCount = 5.f;

	if (DifficultyCurve)
	{
		MaxBotsCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NrOfAliveBots >= MaxBotsCount)
	{
		UE_LOG(LogTemp, Log, TEXT("Max bot capacity. Skipping bot spawn"));
		return;
	}


	// Run EQS and spawn bots
	FEnvQueryRequest Request(SpawnBotQuery, this);
	Request.Execute(EEnvQueryRunMode::RandomBest5Pct, this, &ARGameModeBase::OnBotSpawnQueryCompleted);
}

void ARGameModeBase::OnBotSpawnQueryCompleted(TSharedPtr<FEnvQueryResult> Result)
{
	// Accessing a raw pointer is slightly faster 
	FEnvQueryResult* QueryResult = Result.Get();
	if (!QueryResult->IsSuccessful())
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Bots EQS Failed!"));
		return;
	}

	TArray<FVector> Locations;
	QueryResult->GetAllAsLocations(Locations);

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(BotClass, Locations[0], FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Emerald, false, 50.0f);
	}
}
