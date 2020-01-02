// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Frame/MyManagerBase.h"
#include "Character/Enemy/EnemyType.h"
#include "EnemySpawnManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class APROJECT_API UEnemySpawnManager : public UMyManagerBase
{
	GENERATED_BODY()
public:
	UEnemySpawnManager();
public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category="EnemyPool")
	TArray<EEnemyType> EnemyPool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyPool")
	TArray<class AEnemyCharacter*> EnemySpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyPool")
		TMap<EEnemyType,class UClass*> EnemyStaticClass;

	virtual void ManagerInit() override;
public:
	UFUNCTION()
	void Spawn();
	void SpawnActor(EEnemyType EnemyType, FTransform Trn);
	void OnStartSpawn(UWorld* World);

private:
	UWorld* CurrentWorld;
};
