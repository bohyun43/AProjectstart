// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "EnemyCharacter.h"
AEnemyAIController::AEnemyAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
}

void AEnemyAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(InPawn);
	if (Enemy &&
		Enemy->EnemyBehaviorTree &&
		Enemy->EnemyBehaviorTree->BlackboardAsset) //Zombie가 AI 설정이 되어 있으면
	{
		BBComponent->InitializeBlackboard(*(Enemy->EnemyBehaviorTree->BlackboardAsset));
		BTComponent->StartTree(*(Enemy->EnemyBehaviorTree));

		BBComponent->SetValueAsFloat(FName(TEXT("WaitTime")), 2.0f);
		BBComponent->SetValueAsVector(FName(TEXT("Target")), FVector(100, 100, 100));
	}
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	BTComponent->StopTree();
}
