// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Character/MyCharacter.h"
#include "Character/MyActor.h"
#include "DefenceWallActor.generated.h"


UENUM(BlueprintType)
enum class EDefenceWallType : uint8
{
	None = 0			UMETA(Display = "None"),
	Normal = 1			UMETA(Display = "Normal"),
	End = 2				UMETA(Display = "End"),
};

UENUM(BlueprintType)
enum class EDefenceWallState : uint8
{
	None = 0			UMETA(Display = "None"),
	Normal = 1			UMETA(Display = "Normal"),
	Attacked = 2		UMETA(Display = "Attacked"),
	Care = 3			UMETA(Display = "Care"),
	Destory = 4			UMETA(Display = "Destory"),
};

/**
 * 
 */
UCLASS(HideCategories = (Camera, Replication, Actor, Input, LOD, Collision, Cooking, Rendering))
class APROJECT_API ADefenceWallActor : public AMyActor
{
	GENERATED_BODY()
public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	void DestoryActor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		EDefenceWallType DefenceWallType = EDefenceWallType::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		EDefenceWallState DefenceWallState = EDefenceWallState::Normal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		int32 Index = 0;
};
