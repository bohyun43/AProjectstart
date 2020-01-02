// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyManagerDef.h"
#include "MyMessageBase.h"
#include "MySystemSingleton.generated.h"

/*
 * [������Ʈ ����] > [���� - �Ϲݼ��� - ���] > Game Singleton Class ��� : (Blueprint�� �Ļ� Ŭ���� ������, ManagerRegistry ��� �ʿ�.)
 */
UCLASS(Blueprintable, BlueprintType)      
class APROJECT_API UMySystemSingleton : public UObject
{
	GENERATED_BODY()
	
public:

	UMySystemSingleton(const FObjectInitializer& ObjectInitializer);
	~UMySystemSingleton();

	// ����� �ý��� �߰�.
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

	// Frame ����/�Ҹ� > GameInstance ȣ���
	void SystemInit(TWeakObjectPtr<class UMyGameInstance>  gameInstance);
	void SystemDrop();
	
	// Frame �غ�/���� > GameMode ȣ���
	void SystemStandBy();
	void SystemBegin();
	void SystemTick(float deltaTime);
	void SystemEnd();

	// �޼��� ó�� ����
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
