// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyCharacter.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEnemyState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
