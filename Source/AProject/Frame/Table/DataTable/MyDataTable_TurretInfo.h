// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MyDataTable_TurretInfo.generated.h"


USTRUCT(BlueprintType)
struct FTurrentInfoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FTurrentInfoData()
		: index(0)
		, Name("")
		, Damage(0.0f)
		, Delay(0.0f)
		, BP("")
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurretInfo)
		int32 index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurretInfo)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurretInfo)
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurretInfo)
		float Delay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurretInfo)
		FString BP;
};

/**
 * 
 */
UCLASS()
class APROJECT_API UMyDataTable_TurretInfo : public UDataTable
{
	GENERATED_BODY()
	
};
