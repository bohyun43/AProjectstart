// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/MyGameStateBase.h"
#include "MyBattleGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AMyBattleGameStateBase : public AMyGameStateBase
{
	GENERATED_BODY()
public:
	AMyBattleGameStateBase(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(config)
		float PokerTime;
	UPROPERTY(config)
		float DefenceTime;
	UPROPERTY()
		float CurrentTime;
	/** Game state. */
	EGamePlayState GamePlayState;
	//
	//EGameplayState::Type GameplayState;
public:
	virtual void StartGamePlayStateMachine() override;
	virtual void SetGamePlayState(EGamePlayState NewState) override;
	virtual void Tick(float DeltaTime) override;

private:
	void StartGamePlay();
};
