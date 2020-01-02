// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Character/Tower/MyTower.h"
#include "MyMissileTurret.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AMyMissileTurret : public AMyTower
{
	GENERATED_BODY()

	AMyMissileTurret();
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UParticleSystem* MuzzleFlash;

public:
	virtual void OnFire() override;

	virtual void BeginPlay() override;


	
};
