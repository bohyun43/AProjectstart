// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Frame/MyManagerBase.h"
#include "MyUMGManager.generated.h"



/*
 * 
 */
UCLASS()
class APROJECT_API UMyUMGManager : public UMyManagerBase
{
	GENERATED_BODY()
	
public:
	UMyUMGManager();

	// Override
	virtual void FinishDestroy() override;		// UObject GC 해제

	virtual void ManagerInit() override;
	virtual void ManagerClear() override;

	virtual void ManagerStandBy() override;
	virtual void ManagerBegin() override;
	virtual void ManagerTick(float deltaTime) override;
	virtual void ManagerEnd() override;
	

	// Support Function
	void CreateUMG();
	void DestroyUMG();

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//	TSubclassOf<class UUIBattleMain> BattleMainClass;
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	//	class UUIBattleMain* BattleMain;

	//void VisiblePannel(EUIPanel UIPanel, ESlateVisibility Visible);

protected:



private:

	//// 입력 Actor : SharedPtr 역할.
	//UPROPERTY()
	//class ADialogInputPawn* InputPawn;	
};
