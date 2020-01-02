// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBattleGameStateBase.h"

#include "EnemySpawnManager.h"
#include "MySystemSingleton.h"
#include "MyManagerBase.h"
#include "Battle/MyBattlePlayerController.h"
#include "Kismet/GameplayStatics.h"


AMyBattleGameStateBase::AMyBattleGameStateBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	PokerTime = 60.0f;
	DefenceTime = 60.0f;
	CurrentTime = 0.0f;

	GamePlayState = EGamePlayState::None;
}
void AMyBattleGameStateBase::Tick(float DeltaTime)
{
	CurrentTime += DeltaTime;

	if (GamePlayState == EGamePlayState::Poker)
	{
		if (CurrentTime > PokerTime)
		{
			SetGamePlayState(EGamePlayState::Defence);
			CurrentTime = 0.0f;
		}
	}
	else if (GamePlayState == EGamePlayState::Defence)
	{
		if (CurrentTime > DefenceTime)
		{
			SetGamePlayState(EGamePlayState::Poker);
			CurrentTime = 0.0f;
		}
	}

	AMyBattlePlayerController* PC = Cast<AMyBattlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		int8 LeftTime = 60 - CurrentTime;
		PC->SetLeftTime(LeftTime);
	}
}
void AMyBattleGameStateBase::StartGamePlayStateMachine()
{
	FTimerHandle StartGameHandle;
	FTimerManager& TimeManager = GetWorld()->GetTimerManager();
	TimeManager.SetTimer(StartGameHandle, this, &AMyBattleGameStateBase::StartGamePlay, 1.0f);
}

void AMyBattleGameStateBase::StartGamePlay()
{
	SetGamePlayState(EGamePlayState::Poker);
}

void AMyBattleGameStateBase::SetGamePlayState(EGamePlayState NewState)
{
	// 상태가 같으면 리턴
	if (NewState == GamePlayState)
		return;

	GamePlayState = NewState;
	CurrentTime = 0.0f;

	switch (GamePlayState)
	{
		case EGamePlayState::Poker:
		{
			UMySystemSingleton* frameSingleton = MYGet();
			if (frameSingleton && frameSingleton->GetUMG())
			{
				AMyBattlePlayerController* PC = Cast<AMyBattlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

				if (PC)
				{
					PC->SetVisibleWidget(EWidget::BattleMainPanel, ESlateVisibility::Visible);
				}

				//AMyBattlePlayerController* PC = Cast<AMyBattlePlayerController>(GetOwningPlayer());
				//frameSingleton->GetUMG()->VisiblePannel(EUIPanel::BattleMainPanel, ESlateVisibility::Visible);
			}
		}
		break;
		case EGamePlayState::Defence:
		{
			UMySystemSingleton* frameSingleton = Cast<UMySystemSingleton>(GEngine->GameSingleton);
			if (frameSingleton)
			{
				UEnemySpawnManager* Spawn = frameSingleton->GetEnemySpawn();
				if (Spawn)
				{
					Spawn->OnStartSpawn(GetWorld());
				}

				AMyBattlePlayerController* PC = Cast<AMyBattlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

				if (PC)
				{
					PC->CreateTower();
					PC->SetVisibleWidget(EWidget::BattleMainPanel, ESlateVisibility::Hidden);
				}
			}
		}
		break;
		default:
			break;
	}


}