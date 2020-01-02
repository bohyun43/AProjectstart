// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyType.h"
#include "UserWidget.h"
#include "MyBattlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AMyBattlePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class UUIBattleMain>		BattleMainClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class UMyDebugWidgetBase>	DebugLogClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class UMyMainHudWidgetBase> MainHudClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UUIBattleMain*		BattleMainWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UMyDebugWidgetBase*	DebugLogWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UMyMainHudWidgetBase*		MainHudWidget;
//public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TMap<ECardRule,TSubclassOf<class AMyTower>>		TowerMap;
public:
	virtual void BeginPlay() override;

	void SetVisibleWidget(EWidget Widget, ESlateVisibility Visible);

	void SetLeftTime(int8 Time);

	void CreateTower();
};
