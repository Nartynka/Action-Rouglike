// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"


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
	if (!Result->IsSuccessful())
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Bots EQS Failed!"));
		return;
	}
		
	TArray<FVector> OutLocations;
	Result->GetAllAsLocations(OutLocations);
	
	if (OutLocations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(BotClass, OutLocations[0], FRotator::ZeroRotator);
	}
}
