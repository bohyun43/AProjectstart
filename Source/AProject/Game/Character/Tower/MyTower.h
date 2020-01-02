// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacterState.h"
#include "MyTower.generated.h"

UCLASS()
class APROJECT_API AMyTower : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		float AttackDamage;	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		float AttackSpeed;	// 공속
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		float Radius;		// 사거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		int32 MaxTargetCount;	// 동시 타격 개수

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		TArray<AActor*> ArrTarget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		ETowerType	TowerType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		ELODType	LODType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		float MuzzleFlashScale;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnProjectile();
	UFUNCTION()
		void TowerUpdate();
	UPROPERTY()
	FTimerHandle UpdateGameHandle;

public:
	virtual void OnFire();
	virtual void FindTarget();
	virtual void FindTarget(float RadiusParam );

	float FTestAngle;
	float FCurrentAngle;
	float FLerpTime;
	UPROPERTY()
	AActor* FFTargetActor;
public:
	FTransform ShootPoint;
protected:
	FTransform GetShootTransform();
	UStaticMeshComponent* GetShootPointComponent();
};
