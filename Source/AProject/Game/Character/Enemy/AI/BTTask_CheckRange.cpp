// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckRange.h"
//#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Enemy/EnemyAIController.h"
#include "Character/DefenceActor/DefenceWallActor.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Components/CapsuleComponent.h"

EBTNodeResult::Type UBTTask_CheckRange::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	ADefenceWallActor* DefenceWall = Cast<ADefenceWallActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

	if (!Enemy || !DefenceWall)
	{
		return EBTNodeResult::Failed;
	}

	if (!Enemy->GetCapsuleComponent() || !Enemy->GetCapsuleComponent()->GetScaledCapsuleRadius())
	{
		return EBTNodeResult::Failed;
	}

	float EnemyRadius = Enemy->GetCapsuleComponent()->GetScaledCapsuleRadius();
	float DefenceWallRadius = 50.0f;

	Range = EnemyRadius + DefenceWallRadius + 50.0f;

	float Distance = FVector::Distance(DefenceWall->GetActorLocation(), Enemy->GetActorLocation());

	switch (Condition)
	{
		case ETaskCondition::Less:
		{
			if (Distance < Range)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)TargetState);
				Enemy->SetCurrentState(TargetState);
			}
		}
		break;

		case ETaskCondition::Greater:
		{
			if (Distance > Range)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)TargetState);
				//Enemy->CurrentState = TargetState;
				Enemy->SetCurrentState(TargetState);
			}
		}
		break;
	}

	return EBTNodeResult::Succeeded;
}
