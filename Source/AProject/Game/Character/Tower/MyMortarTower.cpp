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
			// �߻� ��ü ����Ʈ
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld()
				, MuzzleFlash
				, GetShootTransform());

			// ���� �̻��� �߻�
			if (MissileSubClass)
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				// ����
				AMyMortarMissile* MissileActor = GetWorld()->SpawnActor<AMyMortarMissile>(MissileSubClass, GetMissilePoint(), SpawnInfo);

				// Ÿ�� ����
				if (MissileActor)
				{
					MissileActor->Target = EnemyActor;
					MissileActor->Damage = AttackDamage;
					// �ı� �˸� ����
					EnemyActor->AddDestoryDelegateByMissile(MissileActor);
					//MissileActor->EnemyDestory.AddDynamic()
				}
				
				// �ı� �˸� ����
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
