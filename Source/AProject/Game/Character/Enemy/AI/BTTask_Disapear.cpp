// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Disapear.h"

EBTNodeResult::Type UBTTask_Disapear::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	AActor* Enemy = Cast<AActor>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy)
	{
		Enemy->Destroy();
	}
	

	return EBTNodeResult::Succeeded;
}