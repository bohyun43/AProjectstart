// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	AEnemyCharacter* Pawn = Cast<AEnemyCharacter>(TryGetPawnOwner());

	if (Pawn && Pawn->IsValidLowLevel())
	{
		CurrentState = Pawn->GetCurrentState();
		Speed = Pawn->GetCharacterMovement()->Velocity.SizeSquared();
	}
}