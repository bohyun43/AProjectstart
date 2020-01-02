// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckTarget.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Enemy/EnemyAIController.h"
#include "Character/DefenceActor/DefenceWallActor.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_CheckTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// 타겟 검증
	bool IsNullTarget = false;
	UObject* Obj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("NextTargetActor"));
	if (Obj == nullptr )
	{
		IsNullTarget = true;
	}

	ADefenceWallActor* Target = Cast<ADefenceWallActor>(Obj);

	if (Target == nullptr)
	{
		IsNullTarget = true;
	}

	// 파괴된 오브젝트 인가
	if (Target->DefenceWallState == EDefenceWallState::Destory
		|| Target->DefenceWallState == EDefenceWallState::None)
	{
		IsNullTarget = true;
	}

	//if (Target->StateHP.GetCurrentHP() <= 0.0f)
	//{
	//	IsNullTarget = true;
	//}

	if (IsNullTarget == true)
	{
		// BlockBoard
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)EEnemyState::Normal);
		//OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("NextTarget")), Target->GetActorLocation());
		//OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("NextTargetActor")), Cast<UObject>(Target));

		// Animation
		if (OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetPawn())
		{
			AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
			if (Enemy)
			{
				Enemy->SetCurrentState(EEnemyState::Normal);
			}
		}
	}

	return EBTNodeResult::Succeeded;
}