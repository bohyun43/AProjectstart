// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EnemyAttack.h"
#include "Character/Enemy/EnemyAIController.h"
#include "Character/DefenceActor/DefenceWallActor.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UAnimNotify_EnemyAttack::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	APawn* Enemy = Cast<APawn>(MeshComp->GetOwner());
	check(Enemy);

	AEnemyAIController* AI = Cast<AEnemyAIController>(Enemy->GetController());
	check(AI);

	ADefenceWallActor* TargetActor = Cast<ADefenceWallActor>(AI->BBComponent->GetValueAsObject(FName(TEXT("NextTargetActor"))));
	if (TargetActor)
	{
		UGameplayStatics::ApplyDamage(TargetActor, 1.0f, AI, Enemy, nullptr);
	}
}
