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

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ARGameModeBase::SpawnBots_TimeElapsed, SpawnTimerInterval, true);
}

void ARGameModeBase::SpawnBots_TimeElapsed()
{
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
	

	int32 NrOfAliveBots = 0;

	for (TActorIterator<ARAICharacter> It(GetWorld()); It; ++It)
	{
		ARAICharacter* Bot = *It;
		URAttributeComponent* AttributeComp = Bot->GetComponentByClass<URAttributeComponent>();

		if (AttributeComp && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	float MaxBotsCount = 5.f;

	if (DifficultyCurve)
	{
		MaxBotsCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NrOfAliveBots >= MaxBotsCount)
	{
		return;
	}

	TArray<FVector> OutLocations;
	QueryResult->GetAllAsLocations(OutLocations);
	

	if (OutLocations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(BotClass, OutLocations[0], FRotator::ZeroRotator);
	}
}
