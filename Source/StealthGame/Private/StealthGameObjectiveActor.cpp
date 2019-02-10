// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthGameObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h" // For spawning particle FX
#include "StealthGameCharacter.h"

// Sets default values
AStealthGameObjectiveActor::AStealthGameObjectiveActor()
{
	// Mesh component setup
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Sphere component setup
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AStealthGameObjectiveActor::PostInitProperties()
{
	Super::PostInitProperties();
}

// Called when the game starts or when spawned
void AStealthGameObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
}

void AStealthGameObjectiveActor::PlayEffects()
{
	if (PickupFX != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
	}

	if (PickupSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}
}

void AStealthGameObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AStealthGameCharacter* MyCharacter = Cast<AStealthGameCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->bIsCarryingObjective = true;
		PlayEffects();
		Destroy();
	}
}

