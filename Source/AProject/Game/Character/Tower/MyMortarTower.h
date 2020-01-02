// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Character/Tower/MyTower.h"

#include "MyMortarTower.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AMyMortarTower : public AMyTower
{
	GENERATED_BODY()
public:
	AMyMortarTower();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
		class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		TSubclassOf<class AMyMortarMissile> MissileSubClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
		float MissileScale;
	
	virtual void OnFire() override;
public:
	FTransform MissilePoint;
protected:
	FTransform GetMissilePoint();
};
