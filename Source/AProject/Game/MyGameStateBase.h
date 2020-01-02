// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyType.h"
#include "MyGameStateBase.generated.h"


UENUM(BlueprintType)
enum class EGamePlayState : uint8
{
	None = 0			UMETA(Display = "None"),
	Poker = 1			UMETA(Display = "Poker"),
	Defence = 2			UMETA(Display = "Defence"),
};

/**
 * 
 */
UCLASS()
class APROJECT_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMyGameStateBase(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(config)
		int32 WarmupTime;

public:
	virtual void StartGamePlayStateMachine();

	virtual void SetGamePlayState(EGamePlayState NewState);

	virtual void Tick(float DeltaTime) override;
};
