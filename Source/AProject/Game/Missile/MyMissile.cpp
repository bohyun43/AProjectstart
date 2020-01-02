// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMissile.h"
#include "Components/BoxComponent.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Missile/MyDamageTypeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyMissile::AMyMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

// Construct Collision Component
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	// Construct Static Mesh Component
	MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
	//const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Missile/Missile_01_Model"));
	//MissileMesh->SetStaticMesh(MeshObj.Object);
	MissileMesh->SetupAttachment(RootComponent);

	// Construct Projectile Movement Component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 200.f;
	ProjectileMovement->MaxSpeed = 300.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bIsHomingProjectile = false;
	ProjectileMovement->HomingAccelerationMagnitude = 0.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->Velocity = FVector(0, 0, 0);

	// Bind our OnOverlapBegin Event
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyMissile::OnOverlapBegin);

	// Set Default Values for Variables
	Target = NULL;
	Lifetime = 5.f;
	DelayTime = 0.1f;
	Magnitude = 2000.0f;
	IsSetHoming = false;
	CanReTarget = false;
	DamageType = EMyDamageType::None;
	Damage = 1.0f;
	ReTargetCount = 0;
	//PlayerInWorld = NULL;
}

// Called when the game starts or when spawned
void AMyMissile::BeginPlay()
{
	Super::BeginPlay();
	// Before we find our target, launch the Missile upwards
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = GetActorUpVector() * ProjectileMovement->InitialSpeed;
	}
	
	// BeginPlay with collision disabled so that the missile doesn't interact with other actors
	this->SetActorEnableCollision(false);

	FTimerHandle StartGameHandle;
	if (GetWorld())
	{
		FTimerManager& TimeManager = GetWorld()->GetTimerManager();
		TimeManager.SetTimer(StartGameHandle, this, &AMyMissile::SetHoming, DelayTime);
	}
}

// Called every frame
void AMyMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AMyMissile::SetHoming()
{
	IsSetHoming = true;
	this->SetActorEnableCollision(true);

	if (ProjectileMovement)
	{
		ProjectileMovement->bIsHomingProjectile = true;
		ProjectileMovement->HomingTargetComponent = Target->GetCapsuleComponent();
		ProjectileMovement->HomingAccelerationMagnitude = Magnitude;
	}
}
#pragma region Overlap Events
// If our missile overlaps the player or the ground, it will be destroyed
void AMyMissile::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &hitResult)
{
	if (otherActor->ActorHasTag(TEXT("Missile")) == true)
	{
		return;
	}
	
	if (otherActor->ActorHasTag(TEXT("Tower")) == true)
	{
		return;
	}
	
	class AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(otherActor);

	if (EnemyCharacter != nullptr)
	{
		Explode();

		//EnemyCharacter->SetDamage(Damage);
		FHitResult HitResult;
		UGameplayStatics::ApplyPointDamage(otherActor, Damage, FVector::ZeroVector, HitResult, nullptr, this, UMyDamageTypeBase::StaticClass());

	}

	Explode();

	//class AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(otherActor);
	//class AStaticMeshActor* GroundActor = Cast<AStaticMeshActor>(otherActor);

	//if (PlayerCharacter != nullptr)
	//{
	//	Explode();
	//}

	//if (GroundActor != nullptr)
	//{
	//	Explode();
	//}

	//if (PlayerCharacter == nullptr)
	//{
	//	Explode();
	//}
	
}
#pragma endregion

#pragma region End of Play Logic
// Our destroy method
void AMyMissile::Explode()
{
	PlayExplosion(ExplosionSystem);
	PlayExplosionSound(ExplosionSound);

	if (this->IsValidLowLevel()) 
	{
		this->SetActorEnableCollision(false);
		//this->SetActorHiddenInGame(true);
		this->SetLifeSpan(2.0f);
		ProjectileMovement->bIsHomingProjectile = false;
		ProjectileMovement->HomingAccelerationMagnitude = 0.0f;
		Target = nullptr;
		CanReTarget = false;
	}
		//Destroy();
}

// Spawn our explosion particle system
class UParticleSystemComponent* AMyMissile::PlayExplosion(class UParticleSystem* explosion)
{
	class UParticleSystemComponent* retVal = NULL;

	if (explosion)
	{
		class UWorld* const world = GetWorld();

		if (world)
		{
			FVector myPos = GetActorLocation();
			FRotator myRot = GetActorRotation();

			retVal = UGameplayStatics::SpawnEmitterAtLocation(world, explosion, myPos, myRot, true);
		}
	}

	return retVal;
}

// Spawn our explosion sound
class UAudioComponent* AMyMissile::PlayExplosionSound(class USoundCue *sound)
{
	class UAudioComponent* retVal = NULL;

	if (sound)
		retVal = UGameplayStatics::SpawnSoundAttached(sound, this->GetRootComponent());

	return retVal;
}
#pragma endregion


void AMyMissile::RequestEnemyDestory(AActor* Actor)
{
	_RequestEnemyDestory(Actor);
}

void AMyMissile::_RequestEnemyDestory(AActor* Actor)
{
	int Test = 0;
}

