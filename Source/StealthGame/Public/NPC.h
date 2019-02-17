// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspicious,

	Alerted
};

UCLASS()
class STEALTHGAME_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitProperties() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* PawnSensingComp = nullptr;

	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
		void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginalRotation = FRotator(0);

	UFUNCTION()
		void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnAIStateChanged(EAIState NewState);

	UPROPERTY(EditInstanceOnly, Category = "AI")
		bool bPatrol = false;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor* FirstPatrolPoint = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor* SecondPatrolPoint = nullptr;

	AActor* CurrentPatrolPoint = nullptr;

	void MoveToNextPatrolPoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
