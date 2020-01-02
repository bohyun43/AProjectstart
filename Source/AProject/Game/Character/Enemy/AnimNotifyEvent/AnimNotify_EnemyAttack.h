// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UAnimNotify_EnemyAttack : public UAnimNotify
{
	GENERATED_BODY()
public:
	void Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);
};
