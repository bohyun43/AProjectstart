// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Missile/MyMissile.h"
#include "MyMortarMissile.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AMyMortarMissile : public AMyMissile
{
	GENERATED_BODY()
public:
	AMyMortarMissile();
public:
	virtual void BeginPlay() override;
	// Å¸°Ù ÆÄ±« ¾Ë¸²
	virtual void _RequestEnemyDestory(AActor* Actor) override;
	virtual void Explode() override;
	// Å¸°Ù Àç¼³Á¤
	virtual void ReTarget() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
		class UParticleSystem* MissileFire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
		class UParticleSystem* MissileTail;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* MissileFirePoint;
};
