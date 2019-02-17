// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "StealthGameCharacter.h"
#include "StealthGameGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExtractionZone::AExtractionZone()
{
	// Create and setup overlap component
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	// Create and setup decal component
	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f);
	DecalComp->SetupAttachment(RootComponent);
}

void AExtractionZone::PostInitProperties()
{
	Super::PostInitProperties();
	if (OverlapComp)
	{
		OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::HandleOverlap);
	}
}


void AExtractionZone::HandleOverlap(
	UPrimitiveComponent * OverlappedComponent,
	AActor * OtherActor,
	UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	

	AStealthGameCharacter* MyPawn = Cast<AStealthGameCharacter>(OtherActor);
	if (MyPawn == nullptr)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Overlapped with extraction zone"));
	
	if (MyPawn->bIsCarryingObjective)
	{
		AStealthGameGameMode* GameMode = Cast<AStealthGameGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->CompleteMission(MyPawn, true);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}
}
