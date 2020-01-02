// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnManager.h"
#include "TimerManager.h"
#include "Character/Enemy/EnemyCharacter.h"

UEnemySpawnManager::UEnemySpawnManager()
{
	ManagerType = EManagerType::Mgr_EnemySpawn;

	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::Tron);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::Tron);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::Tron);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::Tron);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::Tron);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::Tron);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::ChibiSkeleton);
	//EnemyPool.Add(EEnemyType::Tron);

	for (int index = 0; index < 20; ++index)
	{
		EnemyPool.Add(EEnemyType::Tron);
	}
}

void UEnemySpawnManager::ManagerInit()
{
	//EnemyStaticClass
	UClass* BP_Enemy_Type_1 = LoadObject< UClass >(nullptr, TEXT("Blueprint'/Game/Blueprints/Character/Enemy/BP_ChibiSkeleton.BP_ChibiSkeleton_C'"));

	EnemyStaticClass.Add(EEnemyType::ChibiSkeleton, BP_Enemy_Type_1);

	UClass* BP_Enemy_Type_2 = LoadObject< UClass >(nullptr, TEXT("Blueprint'/Game/Blueprints/Character/Enemy/BP_Enemy_Sphere.BP_Enemy_Sphere_C'"));

	EnemyStaticClass.Add(EEnemyType::Tron, BP_Enemy_Type_2);
}
void UEnemySpawnManager::Spawn()
{
	TArray<AActor*> Arr;
	UGameplayStatics::GetAllActorsOfClass(CurrentWorld, AActor::StaticClass(), Arr);
	FTransform Trans;
	int32 TargetIndex = MAX_int32;
	for (AActor* Iter : Arr)
	{
		AActor* DActor = Cast<AActor>(Iter);

		if (DActor && DActor->ActorHasTag(TEXT("EnemyStart")))
		{
			Trans = DActor->GetTransform();
		}
	}

	auto MyCharacter = nullptr;
	UClass* BP_Enemy_Select = nullptr;

	float CurrentTime = 0.0f;
	float DelayTime = 2.0f;

	for (auto& iter : EnemyPool)
	{
		EEnemyType Value = iter;

		FTimerHandle StartGameHandle;
		if (CurrentWorld)
		{
			FTimerManager& TimeManager = CurrentWorld->GetTimerManager();
			FTimerDelegate TimerDel;

			FTimerDelegate ExplosionDelegate = FTimerDelegate::CreateLambda([=]()
			{
				this->SpawnActor(Value, Trans);
			});

			TimeManager.SetTimer(StartGameHandle, ExplosionDelegate, CurrentTime, false);

			CurrentTime += DelayTime;
		}
	}
}
void UEnemySpawnManager::SpawnActor(EEnemyType EnemyType , FTransform Trn)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AEnemyCharacter* Enemy = CurrentWorld->SpawnActor<AEnemyCharacter>(EnemyStaticClass[EnemyType], Trn, SpawnInfo);

	Enemy->SetEnemyType(EnemyType);


	EnemySpawn.Add(Enemy);
}
void UEnemySpawnManager::OnStartSpawn(UWorld* World)
{
	FTimerHandle StartGameHandle;
	if (World)
	{
		CurrentWorld = World;
		FTimerManager& TimeManager = World->GetTimerManager();
		TimeManager.SetTimer(StartGameHandle, this, &UEnemySpawnManager::Spawn, 1.0f);
	}
}

