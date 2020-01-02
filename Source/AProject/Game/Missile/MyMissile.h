// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "MyMissile.generated.h"

UCLASS(BlueprintType)
class APROJECT_API AMyMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyMissile();
public:
	// Å¸°Ù ÆÄ±« ¾Ë¸²
	UFUNCTION()
	void RequestEnemyDestory(AActor* Actor);
protected:
	// Å¸°Ù Àç¼³Á¤
	virtual void ReTarget() {}
	virtual void _RequestEnemyDestory(AActor* Actor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		// Event to Detect When an Actor Overlaps the Missile Class
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &hitResult);
public:
	// Delay Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float DelayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Magnitude;
	// Actor Lifetime Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Lifetime;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	//USceneComponent* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	class AEnemyCharacter* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool CanReTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMyDamageType DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Damage;
	

	bool IsSetHoming;

	UFUNCTION()
	void SetHoming();

	virtual void Explode();

	int32 ReTargetCount;
public:
	// Collision Component for Missile Class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* CollisionComp;
		// Static Mesh Component for Missile Class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* MissileMesh;
		// Projectile Movement Component for Missile Class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* ProjectileMovement;
		// Explosion
	UPROPERTY(EditDefaultsOnly, Category = "FX")
		class UParticleSystem* ExplosionSystem;
	class UParticleSystemComponent* PlayExplosion(class UParticleSystem* explosion);
	// Sounds
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* ExplosionSound;

	class UAudioComponent* PlayExplosionSound(class USoundCue *sound);
};
