// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StealthGameGameMode.generated.h"

UCLASS(minimalapi)
class AStealthGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
		TSubclassOf<AActor> SpectatingViewpointClass;
public:
	AStealthGameGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool bMissionSucess);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSucess);
};



