// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBattlePlayerController.h"
#include "UI/UIBattleMain.h"
#include "UI/MyDebugWidgetBase.h"
#include "UI/MyMainHudWidgetBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Tower/MyMissileTurret.h"
#include "Character/Tower/MyMortarTower.h"

void AMyBattlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());


	if (BattleMainClass && IsLocalController())
	{
		BattleMainWidget = Cast<UUIBattleMain>(CreateWidget(this, BattleMainClass));
		if (BattleMainWidget)
		{
			BattleMainWidget->AddToViewport();
			BattleMainWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (DebugLogClass && IsLocalController())
	{
		DebugLogWidget = Cast<UMyDebugWidgetBase>(CreateWidget(this, DebugLogClass));
		if (DebugLogWidget)
		{
			DebugLogWidget->AddToViewport();
			DebugLogWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}

	if (MainHudClass && IsLocalController())
	{
		MainHudWidget = Cast<UMyMainHudWidgetBase>(CreateWidget(this, MainHudClass));
		if (MainHudWidget)
		{
			MainHudWidget->AddToViewport();
			MainHudWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}


}

void AMyBattlePlayerController::CreateTower()
{
	/*UClass* BP_Tower = LoadObject< UClass >(nullptr, TEXT("Blueprint'/Game/Blueprints/Character/Tower/BP_Normal.BP_Normal_C'"));*/


	
	UClass* BP_Tower = Cast<UClass>(TowerMap.FindRef(ECardRule::NoPair));
	if (BP_Tower == nullptr )
	{
		return;
	}

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AMyMissileTurret* Tower = GetWorld()->SpawnActor<AMyMissileTurret>(BP_Tower, SpawnInfo);

	
	Tower->SetActorLocation(FVector(Tower->GetActorLocation().X, Tower->GetActorLocation().Y , 100.0f));
}

void AMyBattlePlayerController::SetVisibleWidget(EWidget Widget, ESlateVisibility Visible)
{
	UUserWidget* UserWidget = nullptr;

	switch (Widget)
	{
		case EWidget::None:

			break;
		case EWidget::BattleMainPanel:
		{
			UserWidget = Cast<UUserWidget>(BattleMainWidget);

			if (UserWidget && Visible == ESlateVisibility::Hidden )
			{
				Cast<UUIBattleMain>(UserWidget)->ResetCard();
			}
		}
		break;
		default:
			break;
	}

	if (UserWidget)
	{
		UserWidget->SetVisibility(Visible);
	}
}

void AMyBattlePlayerController::SetLeftTime(int8 Time)
{
	if (DebugLogWidget)
	{
		DebugLogWidget->SetLeftTime(Time);
	}
}