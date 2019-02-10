// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StealthGameObjectiveActor.generated.h"

class USphereComponent;

UCLASS()
class STEALTHGAME_API AStealthGameObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStealthGameObjectiveActor();

protected:

	virtual void PostInitProperties() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* SphereComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
		UParticleSystem* PickupFX = nullptr;

	void PlayEffects();

public:	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
