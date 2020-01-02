// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Character/Tower/MyTower.h"
#include "MyFlamethrower.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AMyFlamethrower : public AMyTower
{
	GENERATED_BODY()

	AMyFlamethrower();
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UParticleSystemComponent* Particle;

public:
	virtual void OnFire() override;

	virtual void BeginPlay() override;

		// Called every frame
	virtual void Tick(float DeltaTime) override;
};
