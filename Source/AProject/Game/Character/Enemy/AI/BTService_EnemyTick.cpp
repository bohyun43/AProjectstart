// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_EnemyTick.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/EnemyAIController.h"
#include "Character/Enemy/EnemyCharacter.h"

void UBTService_EnemyTick::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AEnemyAIController* AI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (AI && AI->GetPawn() )
	{
		AEnemyCharacter* Pawn = Cast<AEnemyCharacter>(AI->GetPawn());
		if (Pawn && OwnerComp.GetBlackboardComponent() )
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)Pawn->GetCurrentState());
		}
	}
}