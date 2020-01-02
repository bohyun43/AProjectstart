// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "MyDamageTypeBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMyDamageType : uint8
{
	None = 0			UMETA(Display = "None"),
	Normal = 1			UMETA(Display = "Normal"),

};

UCLASS()
class APROJECT_API UMyDamageTypeBase : public UDamageType
{
	GENERATED_BODY()
public:
	UMyDamageTypeBase();
public:
	float damage = 3.0f;

	EMyDamageType DamageType = EMyDamageType::Normal;
};
