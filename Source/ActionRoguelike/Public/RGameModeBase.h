// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

#include "RGameModeBase.generated.h"

class UEnvQuery;
class UCurveFloat;

UCLASS()
class ACTIONROGUELIKE_API ARGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> BotClass;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UCurveFloat* DifficultyCurve;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnBotQuery;

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	bool bShouldSpawnBots = true;

	void SpawnBots_TimeElapsed();

	void OnBotSpawnQueryCompleted(TSharedPtr<FEnvQueryResult> Result);

public:

	ARGameModeBase();

	virtual void StartPlay() override;

};
