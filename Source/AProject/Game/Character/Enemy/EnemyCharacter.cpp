// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Missile/MyDamageTypeBase.h"
#include "Missile/MyMissile.h"
#include "Character/Tower/MyTower.h"
#include "Kismet/GameplayStatics.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	AutoPossessAI = EAutoPossessAI::Spawned;

	HitEffectScale = 1.0f;

}
float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);
		if (PointDamageEvent)
		{
			TSubclassOf<UDamageType> Type = PointDamageEvent->DamageTypeClass;
			UMyDamageTypeBase* Base = Cast<UMyDamageTypeBase>(Type.GetDefaultObject());
		}
		
		UParticleSystem* CurrentParticleSystem = nullptr;

		AMyTower* Causer = Cast<AMyTower>(DamageCauser);
		if (Causer)
		{
			switch (Causer->TowerType)
			{
				case ETowerType::None:
				{

				}
				break;
				case ETowerType::Missile:
				{
					CurrentParticleSystem = HitEffect;

					FTransform Trn = GetActorTransform();
					Trn.SetScale3D(FVector(HitEffectScale, HitEffectScale, HitEffectScale));

					UGameplayStatics::SpawnEmitterAtLocation(
						GetWorld()
						, CurrentParticleSystem
						, Trn);
				}
				break;
				case ETowerType::Flamethrower:
				{
					CurrentParticleSystem = HitEffect_Flamethrower;

					
					if (Particle == nullptr)
					{
						Particle = UGameplayStatics::SpawnEmitterAttached(CurrentParticleSystem, RootComponent, FName(TEXT("Flamethrower")), this->GetActorLocation(), this->GetActorRotation(), EAttachLocation::KeepWorldPosition);

						//Particle->SetupAttachment(RootComponent);
					}

					if (Particle)
					{
						Particle->SetFloatParameter(FName(TEXT("LifeTime")), 1.0f);
					}

				}
				break;
				
				default:
					break;
			}
		}

		//if (CurrentParticleSystem)
		//{
		//	FTransform Trn = GetActorTransform();
		//	Trn.SetScale3D(FVector(HitEffectScale, HitEffectScale, HitEffectScale));

		//	UGameplayStatics::SpawnEmitterAtLocation(
		//		GetWorld()
		//		, CurrentParticleSystem
		//		, Trn);
		//}


		SetDamage(DamageAmount);
	}
	return DamageAmount;
}
void AEnemyCharacter::SetDamage(float DamageAmount)
{
	StateHP.TakeDamage(DamageAmount);

	StateHP.SetCurrentHP(FMath::Clamp<float>(StateHP.GetCurrentHP(), 0, StateHP.GetMaxHP()));

	UStaticMeshComponent* HP = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HP")));
	if (HP)
	{
		float Value = StateHP.GetCurrentHP() / StateHP.GetMaxHP();

		HP->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1 - Value, Value, 0));
	}

	CheckDestory();
}
void AEnemyCharacter::CheckDestory()
{
	if (StateHP.GetCurrentHP() == 0)
	{
		// Change State
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetCurrentState(EEnemyState::Dead);

		// Broadcast
		DestoryDelegate.Broadcast(Cast<AActor>(this));

		// Post Action Event
		DestoryActionEvent();
	}


	
}
void AEnemyCharacter::SetCurrentState(EEnemyState State)
{
	CurrentState = State;
}

void AEnemyCharacter::SetEnemyType(EEnemyType Type)
{
	EnemyType = Type;

	switch (Type)
	{
		case EEnemyType::ChibiSkeleton:
		{
			SetMaxHP(10);
			SetAttackType(EEnemyAttackType::Melee);
		}
		break;
		case EEnemyType::Tron:
		{
			SetMaxHP(5);
			SetAttackType(EEnemyAttackType::Melee);
		}
		break;
		default:
			break;
	}
}

void AEnemyCharacter::AddDestoryDelegateByMissile(AMyMissile* Actor)
{
	DestoryDelegate.AddDynamic(Actor, &AMyMissile::RequestEnemyDestory);
}