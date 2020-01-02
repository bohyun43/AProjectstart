// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyType.generated.h"


#define MYGet() Cast<UMySystemSingleton>(GEngine->GameSingleton)

UENUM(BlueprintType)
namespace EGameplayStateOld
{
	enum Type
	{
		Waiting,
		Playing,
		Finished,
	};
}


UENUM(BlueprintType)
enum class EWidget : uint8
{
	None = 0				UMETA(Display = "None"),
	BattleMainPanel = 1		UMETA(Display = "BattleMainPanel"),
	BattleMainHud = 2		UMETA(Display = "BattleMainHud"),
	BattleDebugWidget = 3	UMETA(Display = "BattleDebugWidget"),

};

UENUM(BlueprintType)
enum class EGameLevel : uint8
{
	Easy = 0		UMETA(Display = "Easy"),
	Normal = 1		UMETA(Display = "Normal"),
	Hard = 2		UMETA(Display = "Hard"),

	Max = 4		UMETA(Display = "Max"),
};

UENUM(BlueprintType)
enum class ECardType : uint8
{
	Spades = 0		UMETA(Display = "Spades"),
	Clubs = 1		UMETA(Display = "Clubs"),
	Diamonds = 2		UMETA(Display = "Diamonds"),
	Hearts = 3		UMETA(Display = "Hearts"),

	Max = 4		UMETA(Display = "Max"),
};

UENUM(BlueprintType)
enum class ECardRule : uint8
{
	RoyalStraightFlush = 0	UMETA(Display = "RoyalStraightFlush"),
	BackStraightFlush = 1	UMETA(Display = "BackStraightFlush"),
	StraightFlush = 2		UMETA(Display = "StraightFlush"),
	FourofaKind = 3			UMETA(Display = "FourofaKind"),
	FullHouse = 4			UMETA(Display = "FullHouse"),
	Flush = 5				UMETA(Display = "Flush"),
	Mountain = 6			UMETA(Display = "Mountain"),
	Straight = 7			UMETA(Display = "Straight"),
	BackStraight = 8		UMETA(Display = "BackStraight"),
	TreeofaKind = 9			UMETA(Display = "TreeofaKind"),
	TwoPair = 10			UMETA(Display = "TwoPair"),
	AceOnePair = 11			UMETA(Display = "AceOnePair"),
	OnePair = 12			UMETA(Display = "OnePair"),
	NoPair = 13				UMETA(Display = "NoPair"),
};


UENUM(BlueprintType)
enum class ELODType : uint8
{
	LOD_0 = 0		UMETA(Display = "LOD_0"),
	LOD_1 = 1		UMETA(Display = "LOD_1"),
	LOD_2 = 2		UMETA(Display = "LOD_2"),
	Max = 4		UMETA(Display = "Max"),
};