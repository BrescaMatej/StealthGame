// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtractionZone.generated.h"

class UBoxComponent;

UCLASS()
class STEALTHGAME_API AExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtractionZone();

protected:
	virtual void PostInitProperties() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* OverlapComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UDecalComponent* DecalComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "SoundFX")
		USoundBase* ObjectiveMissingSound = nullptr;

	UFUNCTION()
		void HandleOverlap(
			UPrimitiveComponent * OverlappedComponent,
			AActor * OtherActor,
			UPrimitiveComponent * OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult & SweepResult);

};
