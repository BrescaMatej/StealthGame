// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "StealthGameGameMode.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	GuardState = EAIState::Idle;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalRotation = GetActorRotation();

	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

void ANPC::PostInitProperties()
{
	Super::PostInitProperties();
	
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ANPC::OnPawnSeen);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &ANPC::OnNoiseHeard);

		PawnSensingComp->SensingInterval = 0.2f;
	}
}

void ANPC::OnPawnSeen(APawn * SeenPawn)
{
	if (SeenPawn == nullptr) { return; }

	AStealthGameGameMode* GameMode = Cast<AStealthGameGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->CompleteMission(SeenPawn, false);
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 50.0f, 32, FColor::Blue, false, 0.0f);
	SetGuardState(EAIState::Alerted);

	// Stop if patrolling
	AController* Controller = GetController();
	if (Controller)
	{
		Controller->StopMovement();
	}
}

void ANPC::OnNoiseHeard(APawn* NoiseInstigator, const FVector & Location, float Volume)
{
	if (GuardState == EAIState::Alerted) { return; }
	
	DrawDebugSphere(GetWorld(), Location, 40.0f, 32, FColor::Red, false, 0.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(FRotator( 0.0f, LookAtRotation.Yaw, 0.0f));

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &ANPC::ResetOrientation, 3.0f);

	SetGuardState(EAIState::Suspicious);

	// Stop if patrolling
	AController* Controller = GetController();
	if (Controller)
	{
		Controller->StopMovement();
	}
}

void ANPC::ResetOrientation()
{
	if (GuardState == EAIState::Alerted) { return; }
	
	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::Idle);

	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

void ANPC::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;

	OnAIStateChanged(GuardState);
}

void ANPC::MoveToNextPatrolPoint()
{
	if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
	{
		CurrentPatrolPoint = FirstPatrolPoint;
	}
	else
	{
		CurrentPatrolPoint = SecondPatrolPoint;
	}
	
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Patrol goal checks
	if (CurrentPatrolPoint)
	{
		FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		float DistanceToGoal = Delta.Size();


		if (DistanceToGoal < 100.0f)
		{
			MoveToNextPatrolPoint();
		}
	}
}



