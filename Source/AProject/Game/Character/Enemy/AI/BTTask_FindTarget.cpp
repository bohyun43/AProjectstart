// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Enemy/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Character/DefenceActor/DefenceWallActor.h"

EBTNodeResult::Type UBTTask_FindTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	int32 TargetIndex = MAX_int32;

	UObject* NextTargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("NextTargetActor")));

	if (NextTargetObject)
	{
		ADefenceWallActor* NextTarget = Cast< ADefenceWallActor>(NextTargetObject);

		if (NextTarget)
		{
			TargetIndex = NextTarget->Index + 1;
		}
	}
	
	if (TargetIndex == MAX_int32)
	{
		TargetIndex = 1;
	}

	if (TargetIndex >= 8)
	{
		TargetIndex = TargetIndex - 8;
	}



	TArray<AActor*> Arr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefenceWallActor::StaticClass(), Arr);

	//ADefenceWallActor* EndPoint = nullptr;
	ADefenceWallActor* NextTarget = nullptr;
	//ADefenceWallActor* Target = nullptr;
	//int32 TargetIndex = MAX_int32;
	for (AActor* Iter : Arr)
	{
		ADefenceWallActor* DActor = Cast<ADefenceWallActor>(Iter);

		if (DActor)
		{
			if (DActor->Index == TargetIndex)
			{
				//TargetIndex = Index;
				NextTarget = DActor;
				break;
			}
		}
	}

	//// BlockBoard
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)EEnemyState::Chase);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("NextTarget")), NextTarget->GetActorLocation());
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("NextTargetActor")), Cast<UObject>(NextTarget));
	//OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("EndTargetActor")), Cast<UObject>(EndPoint));

	// Animation
	if (OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetPawn())
	{
		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (Enemy)
		{
			Enemy->SetCurrentState(EEnemyState::Chase);
		}
	}

	return EBTNodeResult::Succeeded;
}

//EBTNodeResult::Type UBTTask_FindTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
//{
//	TArray<AActor*> Arr;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefenceWallActor::StaticClass(), Arr);
//
//	ADefenceWallActor* EndPoint = nullptr;
//	ADefenceWallActor* NextTarget = nullptr;
//	ADefenceWallActor* Target = nullptr;
//	int32 TargetIndex = MAX_int32;
//	for (AActor* Iter : Arr)
//	{
//		ADefenceWallActor* DActor = Cast<ADefenceWallActor>(Iter);
//
//		if (DActor)
//		{
//			if (DActor->DefenceWallState == EDefenceWallState::Destory
//				|| DActor->DefenceWallState == EDefenceWallState::None)
//			{
//				continue;
//			}
//
//			// 도착 지점 체크
//			if (DActor->DefenceWallType == EDefenceWallType::End)
//			{
//				EndPoint = DActor;
//				continue;
//			}
//
//			int32 Index = DActor->Index;
//
//			if (TargetIndex < Index)
//				continue;
//
//			TargetIndex = Index;
//			NextTarget = DActor;
//		}
//	}
//
//	if( EndPoint == nullptr )
//		return EBTNodeResult::Failed;
//
//	if (NextTarget )
//	{
//		Target = NextTarget;
//	}
//	else
//	{
//		Target = EndPoint;
//	}
//
//
//	// BlockBoard
//	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)EEnemyState::Chase);
//	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("NextTarget")), Target->GetActorLocation());
//	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("NextTargetActor")), Cast<UObject>(Target));
//	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("EndTargetActor")), Cast<UObject>(EndPoint));
//	
//	// Animation
//	if (OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetPawn())
//	{
//		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
//		if (Enemy)
//		{
//			Enemy->SetCurrentState(EEnemyState::Chase);
//		}
//	}
//
//	return EBTNodeResult::Succeeded;
//}