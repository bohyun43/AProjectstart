// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFlamethrower.h"
#include "Kismet/GameplayStatics.h"
#include "Missile/MyDamageTypeBase.h"
#include "MyCharacterState.h"
AMyFlamethrower::AMyFlamethrower()
{
	MuzzleFlashScale = 1.0f;

	TowerType = ETowerType::Flamethrower;

	Particle = nullptr;
}
void AMyFlamethrower::OnFire()
{
	for (auto Iter : ArrTarget)
	{
		AActor* Actor = Cast<AActor>(Iter);
		if (Actor)
		{
			UStaticMeshComponent* Point = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Head")));
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

				//FTestAngle = Angle;
				FLerpTime = 0.0f;
				FFTargetActor = Actor;
				//Point->SetRelativeRotation(FRotator(90.0f, Angle, 0));
				//Point->SetRelativeRotation(FRotator(0.0f, Angle, 0));
			}
			
			if (IsValid(Particle) == false)
			{
				Particle = UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GetShootPointComponent(), FName(TEXT("TEST")), GetShootTransform().GetLocation(), GetShootTransform().Rotator(), GetShootTransform().GetScale3D(), EAttachLocation::KeepWorldPosition,false);

				Particle->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
			}

			FHitResult HitResult;

			UGameplayStatics::ApplyPointDamage(Actor, AttackDamage, FVector::ZeroVector, HitResult, nullptr, this, UMyDamageTypeBase::StaticClass());
		}
	}

	SpawnProjectile();
}

void AMyFlamethrower::BeginPlay()
{
	Super::BeginPlay();
}

void AMyFlamethrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Particle != nullptr)
	{
		if (ArrTarget.Num() == 0)
		{
			Particle->Deactivate();
		}
		else
		{
			Particle->Activate();
		}
		
	}
}