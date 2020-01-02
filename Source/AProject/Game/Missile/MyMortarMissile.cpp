// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMortarMissile.h"
#include "EnemySpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "Missile/MyDamageTypeBase.h"
AMyMortarMissile::AMyMortarMissile()
{
	DamageType = EMyDamageType::Normal;

	MissileFirePoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirePoint"));
	MissileFirePoint->SetupAttachment(RootComponent);
	//MissileFirePoint->SetupAttachment(RootComponent)
}
void AMyMortarMissile::BeginPlay()
{
	Super::BeginPlay();
	if (MissileFire != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(MissileFire, MissileMesh, FName(TEXT("FireWorks")), MissileFirePoint->GetComponentLocation(), MissileFirePoint->GetComponentRotation(), EAttachLocation::KeepWorldPosition);
	}

	//if (MissileTail	!= nullptr)
	//{
	//	UGameplayStatics::SpawnEmitterAttached(MissileTail , MissileFirePoint, FName(TEXT("FireTail")), MissileFirePoint->GetComponentLocation(), MissileFirePoint->GetComponentRotation(), EAttachLocation::KeepWorldPosition);
	//}

	
}
void AMyMortarMissile::_RequestEnemyDestory(AActor* Actor)
{
	Super::_RequestEnemyDestory(Actor);

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Actor);
	if (Enemy && Target == Enemy)
	{
		if (CanReTarget)
		{
			ReTarget();
		}
	}
}

void AMyMortarMissile::ReTarget()
{
	if (ReTargetCount > 2)
	{
		this->Destroy();
		return;
	}

	bool IsTarGet = false;

	UEnemySpawnManager* SpawnMgr = MYGet()->GetEnemySpawn();
	if (SpawnMgr)
	{
		for (auto Iter : SpawnMgr->EnemySpawn)
		{
			AEnemyCharacter* Actor = Cast<AEnemyCharacter>(Iter);
			if (Actor == nullptr)
				continue;

			if (Actor->CurrentState == EEnemyState::None)
				continue;

			if (Actor->CurrentState == EEnemyState::Dead)
				continue;

			int32 Index = 0;
			FVector EnemyPos = Actor->GetActorLocation();
			FVector Sub = GetActorLocation() - EnemyPos;

			Target = Actor;

			if (IsSetHoming == true && ProjectileMovement)
			{
				ProjectileMovement->bIsHomingProjectile = true;
				ProjectileMovement->HomingTargetComponent = Target->GetCapsuleComponent();
				ProjectileMovement->HomingAccelerationMagnitude = Magnitude;
			}

			IsTarGet = true;
			break;
		}
	}

	if (IsTarGet == false)
	{
		FTimerHandle ReTargetHandle;
		if (GetWorld())
		{
			++ReTargetCount;
			FTimerManager& TimeManager = GetWorld()->GetTimerManager();
			TimeManager.SetTimer(ReTargetHandle, this, &AMyMortarMissile::ReTarget, 1.0f);
		}
	}
}

void AMyMortarMissile::Explode()
{
	Super::Explode();

	if (MissileMesh)
	{
		MissileMesh->SetVisibility(false, true);
	}
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = FVector::ZeroVector;
	}
	
	if (MissileFirePoint)
	{
		MissileFirePoint->SetVisibility(true, true);
	}
	

}
