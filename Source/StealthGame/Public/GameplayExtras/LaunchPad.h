// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UBoxComponent;

UCLASS()
class STEALTHGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:

	virtual void PostInitProperties() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* OverlapComp = nullptr;

	UFUNCTION()
		void OverlapLaunchPad(
			UPrimitiveComponent * OverlappedComponent,
			AActor * OtherActor,
			UPrimitiveComponent * OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult & SweepResult);

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchStrength = 1000.0f;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchPitchAngle = 45.0f;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchPad")
		UParticleSystem* ActivateLaunchPadEffect = nullptr;
};
