// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyType.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	None = 0			UMETA(Display = "None"),
	Normal = 1			UMETA(Display = "Normal"),
	Battle = 2			UMETA(Display = "Battle"),
	Chase = 3			UMETA(Display = "Chase"),
	Dead = 4			UMETA(Display = "Dead"),
};

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	None = 0			UMETA(Display = "None"),
	ChibiSkeleton = 1	UMETA(Display = "ChibiSkeleton"),
	Tron = 2			UMETA(Display = "Tron"),

};

UENUM(BlueprintType)
enum class EEnemyAttackType : uint8
{
	None = 0			UMETA(Display = "None"),
	Melee = 1			UMETA(Display = "Melee"),

};

