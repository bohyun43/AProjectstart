// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBehaviorTreeComponent* BTComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBlackboardComponent* BBComponent;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
};
