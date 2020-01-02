// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyMessageBase.h"
#include "MyManagerDef.h"
#include "MyManagerBase.generated.h"

// 메세지 Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FManagerBaseMessage, float, msg);

/*
 * 관리자 지원 기반 클래스
 */
UCLASS()
class APROJECT_API UMyManagerBase : public UObject
{
	GENERATED_BODY()
	
public:

	UMyManagerBase();

	// 관리자 초기화/종료
	virtual void ManagerInit();
	virtual void ManagerClear();
	
	// 관리자 준비/해제
	virtual void ManagerStandBy();
	virtual void ManagerBegin();	
	virtual void ManagerTick(float deltaTime);
	virtual void ManagerEnd();

	// 메세지 처리 방식 지원
	virtual void ProcessMessage(MyMessageBase* msg);

	bool IsUpdate()	{ return m_IsUpdate; }
	bool IsEnable() { return m_IsEnable; }
	
public:

	EManagerType GetManagerType()	{ return ManagerType; }
	
	// Engine Delegate Event / World or Core
	virtual void OnPreLoadMap(const FString& mapName) {}
	virtual void OnPostLoadMapWithWorld(UWorld* World) {}

	virtual void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources) {}
	virtual void OnPostWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources) {}

	virtual void OnPostWorldCreation(UWorld* World) {}
	virtual void OnPrevWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS) {}
	virtual void OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS) {}
	virtual void OnPrevWorldFinishDestroy(UWorld* World) {}

	virtual void OnLevelAddedToWorld(ULevel* Level, UWorld* World) {}
	virtual void OnLevelRemovedFromWorld(ULevel* Level, UWorld* World) {}
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FrameSystem, meta = (AllowPrivateAccess = true))
	EManagerType ManagerType;

	UPROPERTY(BlueprintAssignable, Category = FrameSystem, meta = (AllowPrivateAccess = true))
	FManagerBaseMessage	OnMessageDelegate;

protected:
	bool		m_IsEnable;
	bool		m_IsUpdate;
	
private:
	void GetClassVsStaticClass();
};
