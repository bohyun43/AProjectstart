// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include "EnemySpawnManager.h"
#include "MySystemSingleton.h"
#include "MyManagerBase.h"
#include "Battle/MyBattlePlayerController.h"
#include "Kismet/GameplayStatics.h"


AMyGameStateBase::AMyGameStateBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
void AMyGameStateBase::Tick(float DeltaTime)
{
	
}
void AMyGameStateBase::StartGamePlayStateMachine()
{
	
}

void AMyGameStateBase::SetGamePlayState(EGamePlayState NewState)
{

}