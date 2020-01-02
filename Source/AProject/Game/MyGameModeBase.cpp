// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyGameStateBase.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMyGameModeBase::InitGameState()
{
	Super::InitGameState();

	AMyGameStateBase* const GameState = GetGameState<AMyGameStateBase>();
	if (GameState)
	{
		// start the game!
		GameState->StartGamePlayStateMachine();
	}
}