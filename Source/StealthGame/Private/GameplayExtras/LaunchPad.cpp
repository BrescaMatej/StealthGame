// Fill out your copyright notice in the Description page of Project Settings.

#include "LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(75.0f, 75.0f, 50.0f));
	RootComponent = OverlapComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

}

void ALaunchPad::PostInitProperties()
{
	Super::PostInitProperties();

	if (OverlapComp)
	{
		OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::OverlapLaunchPad);
	}
}

void ALaunchPad::OverlapLaunchPad(
	UPrimitiveComponent * OverlappedComponent,
	AActor * OtherActor,
	UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult & SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter)
	{
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
}
