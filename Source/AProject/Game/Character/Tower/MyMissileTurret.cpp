// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMissileTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Missile/MyDamageTypeBase.h"
#include "MyCharacterState.h"
AMyMissileTurret::AMyMissileTurret()
{
	MuzzleFlashScale = 1.0f;

	TowerType = ETowerType::Missile;
}
void AMyMissileTurret::OnFire()
{
	for (auto Iter : ArrTarget)
	{
		AActor* Actor = Cast<AActor>(Iter);
		if (Actor)
		{
			USceneComponent*	Point = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("Head")));
			//UStaticMeshComponent* Point = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Head")));
			if (Point)
			{
				FVector Dir = Actor->GetActorLocation() - GetActorLocation();
				float Dot = FVector::DotProduct(FVector::ForwardVector, Dir.GetSafeNormal());
				FVector Cross = FVector::CrossProduct(FVector::ForwardVector, Dir.GetSafeNormal());
				float AcosAngle = FMath::Acos(Dot);
				float Angle = FMath::RadiansToDegrees(AcosAngle);

				if (Cross.Z < 0.0f)
				{
					Angle = 360 - Angle;
				}

				//Point->SetRelativeRotation(FRotator(90.0f, Angle, 0));
				FTestAngle = Angle;

				//Point->SetRelativeRotation(FRotator(0.0f, Angle, 0));
			}

			
			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, this->GetRootComponent(), FName(TEXT("TEST")), GetShootTransform().GetLocation(), GetShootTransform().Rotator() , GetShootTransform().GetScale3D() , EAttachLocation::KeepWorldPosition, true);

			/*UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld()
				, MuzzleFlash
				, GetMuzzleFlashPoint());*/

			FHitResult HitResult;

			UGameplayStatics::ApplyPointDamage(Actor, AttackDamage, FVector::ZeroVector, HitResult, nullptr, this , UMyDamageTypeBase::StaticClass() );
		}
	}


	SpawnProjectile();
}

void AMyMissileTurret::BeginPlay()
{
	Super::BeginPlay();
}


