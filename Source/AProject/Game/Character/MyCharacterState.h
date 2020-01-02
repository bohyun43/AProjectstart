// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyCharacterState.generated.h"


UENUM(BlueprintType)
enum class ETowerType : uint8
{
	None = 0			UMETA(Display = "None"),
	Missile = 1			UMETA(Display = "Missile"),
	Flamethrower = 2	UMETA(Display = "Flamethrower"),
};


USTRUCT(BlueprintType)
struct FStateHP
{
	GENERATED_USTRUCT_BODY()

	FStateHP()
	{
		CurrentHP = 0.0f;
		MaxHP = 100.0f;
	}
	//virtual ~FStateHP() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float MaxHP = 100.0f;

	void TakeDamage(float Damage)
	{ 
		CurrentHP = CurrentHP - Damage; 
		
		SetCurrentHP(FMath::Clamp<float>(GetCurrentHP(), 0, GetMaxHP()));
	}

	void SetCurrentHP(float HP) { CurrentHP = HP; }
	float GetCurrentHP() { return CurrentHP; }

	void SetMaxHP(float HP) { MaxHP = HP; }
	float GetMaxHP() { return MaxHP; }

	void ResetHP() { CurrentHP = MaxHP; }
};
/**
 * 
 */
UCLASS()
class APROJECT_API UMyState : public UObject
{
	GENERATED_BODY()
};
