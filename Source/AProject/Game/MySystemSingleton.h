// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyManagerDef.h"
#include "MyMessageBase.h"
#include "MySystemSingleton.generated.h"

/*
 * [프로젝트 설정] > [엔진 - 일반세팅 - 고급] > Game Singleton Class 등록 : (Blueprint로 파생 클래스 생성후, ManagerRegistry 등록 필요.)
 */
UCLASS(Blueprintable, BlueprintType)      
class APROJECT_API UMySystemSingleton : public UObject
{
	GENERATED_BODY()
	
public:

	UMySystemSingleton(const FObjectInitializer& ObjectInitializer);
	~UMySystemSingleton();

	// 등록할 시스템 추가.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FrameSystem)
	TMap<TSubclassOf<class UMyManagerBase>, bool> ManagerRegistry;			// Manager Registry (Used Flag)
		

	// Get Manager
	UFUNCTION(BlueprintPure, Category = FrameSystem, meta = (DisplayName = "GetUMG", Keywords = "UMGManager"))
	class UMyUMGManager*		GetUMG();

	UFUNCTION(BlueprintPure, Category = FrameSystem, meta = (DisplayName = "GetTable", Keywords = "TableManager"))
	class UMyTableManager*		GetTable();


	UFUNCTION(BlueprintPure, Category = FrameSystem, meta = (DisplayName = "GetTable", Keywords = "EnemySpawnManager"))
	class UEnemySpawnManager*	GetEnemySpawn();


protected:
	UPROPERTY(Transient)
	TMap<EManagerType, class UMyManagerBase*> MapManager;


public:

	// Frame 생성/소멸 > GameInstance 호출됨
	void SystemInit(TWeakObjectPtr<class UMyGameInstance>  gameInstance);
	void SystemDrop();
	
	// Frame 준비/해제 > GameMode 호출됨
	void SystemStandBy();
	void SystemBegin();
	void SystemTick(float deltaTime);
	void SystemEnd();

	// 메세지 처리 지원
	void ProcessMessage(MyMessageBase* msg);
		
	class  UMyManagerBase*			GetManager(EManagerType type);	
	TWeakObjectPtr<UMyGameInstance>	GetGameInstance() const { return m_GameInstance; }
	UWorld*							GetGameWorld();
	
		
public:
	
	// Engine Delegate / Core or World
	//--------------------------------------------------

	void OnPreLoadMap(const FString& mapName);
	void OnPostLoadMapWithWorld(UWorld* World);

	void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
	void OnPostWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);

	void OnPostWorldCreation(UWorld* World);
	void OnPrevWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);
	void OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);
	void OnPrevWorldFinishDestroy(UWorld* World);

	void OnLevelAddedToWorld(ULevel* Level, UWorld* World);
	void OnLevelRemovedFromWorld(ULevel* Level, UWorld* World);
	
protected:

	FDelegateHandle		HCore_Core_PreLoadMap;
	FDelegateHandle		HCore_Core_PostLoadMapWithWorld;

	FDelegateHandle		HWorld_WorldCleanup;
	FDelegateHandle		HWorld_PostWorldCleanup;

	FDelegateHandle		HWorld_PostWorldCreation;
	FDelegateHandle		HWorld_PrevWorldInitialization;
	FDelegateHandle		HWorld_PostWorldInitialization;
	FDelegateHandle		HWorld_PrevWorldFinishDestroy;

	FDelegateHandle		HWorld_LevelAddedToWorld;
	FDelegateHandle		HWorld_LevelRemovedFromWorld;

private:

	TWeakObjectPtr<UMyGameInstance> m_GameInstance;	
};
