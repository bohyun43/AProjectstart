// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMortarTower.h"
#include "Kismet/GameplayStatics.h"
#include "Missile/MyDamageTypeBase.h"
#include "Missile/MyMortarMissile.h"
#include "Enemy/EnemyCharacter.h"

AMyMortarTower::AMyMortarTower()
{
	MuzzleFlashScale = 1.0f;

	TowerType = ETowerType::Missile;
}
// Called when the game starts or when spawned
void AMyMortarTower::BeginPlay()
{
	Super::BeginPlay();
}
void AMyMortarTower::OnFire()
{
	for (auto Iter : ArrTarget)
	{
		AEnemyCharacter* EnemyActor = Cast<AEnemyCharacter>(Iter);
		if (EnemyActor)
		{
			// 발사 본체 이펙트
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld()
				, MuzzleFlash
				, GetShootTransform());

			// 유도 미사일 발사
			if (MissileSubClass)
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				// 스폰
				AMyMortarMissile* MissileActor = GetWorld()->SpawnActor<AMyMortarMissile>(MissileSubClass, GetMissilePoint(), SpawnInfo);

				// 타겟 지정
				if (MissileActor)
				{
					MissileActor->Target = EnemyActor;
					MissileActor->Damage = AttackDamage;
					// 파괴 알림 셋팅
					EnemyActor->AddDestoryDelegateByMissile(MissileActor);
					//MissileActor->EnemyDestory.AddDynamic()
				}
				
				// 파괴 알림 셋팅
			}
		}
	}
	SpawnProjectile();
}

FTransform AMyMortarTower::GetMissilePoint()
{
	UStaticMeshComponent* Point = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("ShootPoint")));

	if (Point == nullptr)
		return FTransform::Identity;

	MissilePoint = Point->GetComponentTransform();
	MissilePoint.SetScale3D(FVector(MissileScale, MissileScale, MissileScale));

	return MissilePoint;
}
