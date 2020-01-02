// Fill out your copyright notice in the Description page of Project Settings.

#include "MySystemSingleton.h"
#include "MyManagerDef.h"
#include "MyManagerBase.h"

#include "GameDelegates.h"

// Manager Include
#include "MyMessageStruct.h"
#include "MyUMGManager.h"
//#include "FSInputManager.h"
//#include "FSLuaManager.h"
#include "MyTableManager.h"
#include "MyGameInstance.h"
#include "EnemySpawnManager.h"
//#include "FSSoundManager.h"
//#include "FSNetworkManager.h"
//#include "FSStreamingManager.h"
//#include "FSSpawnManager.h"
//#include "FSCameraManager.h"
//#include "FSStateManager.h"


UMySystemSingleton::UMySystemSingleton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	My_LOGCALLF(Log_Base, Log);
}

UMySystemSingleton::~UMySystemSingleton()
{
	My_LOGCALLF(Log_Base, Log);
}

void UMySystemSingleton::SystemInit(TWeakObjectPtr<class UMyGameInstance>  gameInstance)
{
	My_LOGCALLF(Log_Frame, Log);

	check(gameInstance.IsValid());

	m_GameInstance = gameInstance;

	// 등록된 시스템 생성
	for (auto& mgr : ManagerRegistry)
	{
		// 등록 예외.
		if (mgr.Value == false || mgr.Key == nullptr)
			continue;

		// Class Type
		UClass*	registClass = mgr.Key;

		if (registClass != nullptr && registClass->IsChildOf<UMyManagerBase>() == true)
		{
			UMyManagerBase* pCreateMgr = NewObject<UMyManagerBase>(GetTransientPackage(), registClass, registClass->GetFName());
			if (pCreateMgr == nullptr)
				continue;

			My_LOGF(Log_Frame, Log, TEXT("Create Manager : %s"), *registClass->GetFName().ToString());

			MapManager.Add(pCreateMgr->GetManagerType(), pCreateMgr);

			pCreateMgr->ManagerInit();

			switch (pCreateMgr->GetManagerType())
			{
			case EManagerType::Mgr_None:
				continue;

			case EManagerType::Mgr_Config:
			case EManagerType::Mgr_Lua:
			case EManagerType::Mgr_Table:
			case EManagerType::Mgr_Stream:
			case EManagerType::Mgr_Camera:
			case EManagerType::Mgr_Spawn:
			case EManagerType::Mgr_State:
			case EManagerType::Mgr_Level:
			case EManagerType::Mgr_Sound:
			case EManagerType::Mgr_Network:
			case EManagerType::Mgr_UMG:
			case EManagerType::Mgr_EnemySpawn:
				break;
			}
		}
		else
		{
			My_LOGF(Log_Frame, Warning, TEXT("Skip Manager : %s - Not IsChildOf<UMyManagerBase>()"), *registClass->GetFName().ToString());
		}
	}

	// World Delegate 생성

	HCore_Core_PreLoadMap				= FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMySystemSingleton::OnPreLoadMap);
	HCore_Core_PostLoadMapWithWorld		= FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMySystemSingleton::OnPostLoadMapWithWorld);

	HWorld_WorldCleanup					= FWorldDelegates::OnWorldCleanup.AddUObject(this, &UMySystemSingleton::OnWorldCleanup);
	HWorld_PostWorldCleanup				= FWorldDelegates::OnPostWorldCleanup.AddUObject(this, &UMySystemSingleton::OnPostWorldCleanup);
	
	HWorld_PostWorldCreation			= FWorldDelegates::OnPostWorldCreation.AddUObject(this, &UMySystemSingleton::OnPostWorldCreation);
	HWorld_PrevWorldInitialization		= FWorldDelegates::OnPreWorldInitialization.AddUObject(this, &UMySystemSingleton::OnPrevWorldInitialization);
	HWorld_PostWorldInitialization		= FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UMySystemSingleton::OnPostWorldInitialization);
	HWorld_PrevWorldFinishDestroy		= FWorldDelegates::OnPreWorldFinishDestroy.AddUObject(this, &UMySystemSingleton::OnPrevWorldFinishDestroy);

	HWorld_LevelAddedToWorld			= FWorldDelegates::LevelAddedToWorld.AddUObject(this, &UMySystemSingleton::OnLevelAddedToWorld);
	HWorld_LevelRemovedFromWorld		= FWorldDelegates::LevelRemovedFromWorld.AddUObject(this, &UMySystemSingleton::OnLevelRemovedFromWorld);
}

void UMySystemSingleton::SystemDrop()
{
	My_LOGCALLF(Log_Frame, Log);

	// World Delegate 해제
	FWorldDelegates::OnWorldCleanup.Remove			 (HWorld_WorldCleanup);
	FWorldDelegates::OnPostWorldCleanup.Remove		 (HWorld_PostWorldCleanup);

	FWorldDelegates::OnPostWorldCreation.Remove		 (HWorld_PostWorldCreation);
	FWorldDelegates::OnPreWorldInitialization.Remove (HWorld_PrevWorldInitialization);
	FWorldDelegates::OnPostWorldInitialization.Remove(HWorld_PostWorldInitialization);
	FWorldDelegates::OnPreWorldFinishDestroy.Remove	 (HWorld_PrevWorldFinishDestroy);

	FWorldDelegates::LevelAddedToWorld.Remove		 (HWorld_LevelAddedToWorld);
	FWorldDelegates::LevelRemovedFromWorld.Remove	 (HWorld_LevelRemovedFromWorld);
	

	for (auto& mgr : MapManager)
	{
		UMyManagerBase* removeMgr = Cast<UMyManagerBase>(mgr.Value);

		//sys.Key->As(UMyManagerBase::StaticClass)
		if (removeMgr == nullptr) continue;
		if (removeMgr->IsValidLowLevel() == false) continue;

		removeMgr->ManagerClear();

		if (removeMgr->GetClass()->IsChildOf(AActor::StaticClass()) == false)
		{
			// UObject 파생 Destroy
			removeMgr->ConditionalBeginDestroy();
			removeMgr = nullptr;
		}
		else
		{
			AActor* removeMgrActor = Cast<AActor>(mgr.Value);
			// AActor 파생 Destroy
			if (removeMgrActor != nullptr)
			{
				removeMgrActor->Destroy();
				removeMgrActor->ConditionalBeginDestroy();
				removeMgrActor = nullptr;
			}
		}
	}

	MapManager.Empty();

	m_GameInstance = nullptr;
}

// 모든 관리자 준비
void UMySystemSingleton::SystemStandBy()
{
	My_LOGCALLF(Log_Frame, Log);

	// 등록된 시스템 시작
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		//sys.Key->As(UMyManagerBase::StaticClass)
		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->ManagerStandBy();
	}
}

// 모든 관리자 시작
void UMySystemSingleton::SystemBegin()
{
	My_LOGCALLF(Log_Frame, Log);

	// 등록된 시스템 시작
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		//sys.Key->As(UMyManagerBase::StaticClass)
		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->ManagerBegin();
	}
}

void UMySystemSingleton::SystemTick(float deltaTime)
{
	// 등록된 시스템 갱신
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		//sys.Key->As(UMyManagerBase::StaticClass)
		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		if (regMgr->IsUpdate() == true)
			regMgr->ManagerTick(deltaTime);
	}
}

// 모든 관리자 해제
void UMySystemSingleton::SystemEnd()
{
	My_LOGCALLF(Log_Frame, Log);

	// 등록된 시스템 중지
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		//sys.Key->As(UMyManagerBase::StaticClass)
		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->ManagerEnd();
	}
}

void UMySystemSingleton::ProcessMessage(MyMessageBase* msg)
{
	if (msg == nullptr)
		return;

#if WITH_EDITOR

	switch (msg->GetType())
	{
	case EMessageType::Msg_None:
		break;

	case EMessageType::Msg_Host:
		#pragma region Host Message Check
		#pragma endregion
		break;
	case EMessageType::Msg_Server:
		#pragma region Server Message Check
		#pragma endregion
		break;
	//case EMessageType::Msg_Input:
	//	{
	//		#pragma region Input Message Check
	//		FSMessageInput* inputMsg = static_cast<FSMessageInput*>(msg);
	//		if (inputMsg != nullptr)
	//		{
	//			FSInputStruct inputStruct;
	//			inputMsg->SeekMessage(MyMessageBase::Read);
	//			inputMsg->Pop((uint8*)&inputStruct, sizeof(FSInputStruct));
	//			
	//			switch (inputStruct.InputType)
	//			{
	//			case EInputType::INPUT_KEYBOARD:
	//				{
	//					EInputKeyboard keyboard = (EInputKeyboard)inputStruct.InputKey;
	//					My_LOG(Log_Frame, Log, TEXT("ProcessMessage > Type:%s, Cmd:%d Input:%s Key:%s Act:%s" ),
	//						*FSUtil::EnumToString<EMessageType>(TEXT("EMessageType"), msg->GetType()), msg->GetCmd(),
	//						*FSUtil::EnumToString<EInputType>(TEXT("EInputType"),			inputStruct.InputType),
	//						*FSUtil::EnumToString<EInputKeyboard>(TEXT("EInputKeyboard"),	keyboard),
	//						*FSUtil::EnumToString<EInputAction>(TEXT("EInputAction"),		inputStruct.InputAction) );
	//				}
	//				break;
	//			case EInputType::INPUT_MOUSE:
	//				{
	//					EInputMouse mouse = (EInputMouse)inputStruct.InputKey;
	//					My_LOG(Log_Frame, Log, TEXT("ProcessMessage > Type:%s, Cmd:%d Input:%s Btn:%s Act:%s" ),
	//						*FSUtil::EnumToString<EMessageType>(TEXT("EMessageType"), msg->GetType()), msg->GetCmd(),
	//						*FSUtil::EnumToString<EInputType>(TEXT("EInputType"),			inputStruct.InputType),
	//						*FSUtil::EnumToString<EInputMouse>(TEXT("EInputMouse"),			mouse),
	//						*FSUtil::EnumToString<EInputAction>(TEXT("EInputAction"),		inputStruct.InputAction) );
	//				}	
	//				break;
	//			default:
	//				My_LOG(Log_Frame, Log, TEXT("ProcessMessage > Type:%s, Cmd:%d Size:%d"),
	//					*FSUtil::EnumToString<EMessageType>(TEXT("EMessageType"), msg->GetType()), msg->GetCmd(), msg->GetSize());
	//				break;
	//			}
	//		}
	//		#pragma endregion
	//	}
	//	break;
	case EMessageType::Msg_Logic:
		#pragma region Logic Message Check
		#pragma endregion
		break;
	}
#endif

	// 등록된 시스템에 메세지 전달.
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		//sys.Key->As(UMyManagerBase::StaticClass)
		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->ProcessMessage(msg);
	}
}

UMyManagerBase* UMySystemSingleton::GetManager(EManagerType type)
{
	UMyManagerBase** ppMgr = MapManager.Find(type);
	if (ppMgr == nullptr)
		return nullptr;

	return (*ppMgr);
}

UWorld* UMySystemSingleton::GetGameWorld()
{
	if (GetGameInstance() != nullptr)
		return GetGameInstance()->GetWorld();
	return nullptr;
}

// Manager 반환.
class UMyUMGManager*		UMySystemSingleton::GetUMG()		{ return Cast<UMyUMGManager>		(GetManager(EManagerType::Mgr_UMG)); }

class UMyTableManager*		UMySystemSingleton::GetTable()		{ return Cast<UMyTableManager>		(GetManager(EManagerType::Mgr_Table)); }

class UEnemySpawnManager*	UMySystemSingleton::GetEnemySpawn() { return Cast<UEnemySpawnManager>(GetManager(EManagerType::Mgr_EnemySpawn)); }


//class UFSLuaManager*		UMySystemSingleton::GetLua()		{ return Cast<UFSLuaManager>		(GetManager(EManagerType::Mgr_Lua)); }
//class UFSSoundManager*		UMySystemSingleton::GetSound()		{ return Cast<UFSSoundManager>		(GetManager(EManagerType::Mgr_Sound)); }
//class UFSCameraManager*		UMySystemSingleton::GetCamera()		{ return Cast<UFSCameraManager>		(GetManager(EManagerType::Mgr_Camera)); }
//class UFSNetworkManager*	UMySystemSingleton::GetNetwork()	{ return Cast<UFSNetworkManager>	(GetManager(EManagerType::Mgr_Network)); }
//class UFSInputManager*		UMySystemSingleton::GetInput()		{ return Cast<UFSInputManager>		(GetManager(EManagerType::Mgr_Input)); }
//class UFSStreamingManager*	UMySystemSingleton::GetStream()		{ return Cast<UFSStreamingManager>	(GetManager(EManagerType::Mgr_Stream)); }
//class UFSSpawnManager*		UMySystemSingleton::GetSpawn()		{ return Cast<UFSSpawnManager>		(GetManager(EManagerType::Mgr_Spawn)); }
//class UFSStateManager*		UMySystemSingleton::GetState()		{ return Cast<UFSStateManager>		(GetManager(EManagerType::Mgr_State)); }
//class UFSLevelManager*		UMySystemSingleton::GetLevel()		{ return Cast<UFSLevelManager>		(GetManager(EManagerType::Mgr_Level)); }

#pragma region Event_Delegate


void UMySystemSingleton::OnPreLoadMap(const FString& mapName)
{
	My_LOGCALLF(Log_Frame, Log);

	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnPreLoadMap(mapName);
	}
}

void UMySystemSingleton::OnPostLoadMapWithWorld(UWorld* World)
{
	My_LOGCALLF(Log_Frame, Log);

	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnPostLoadMapWithWorld(World);
	}
}

// World 정리 시작시 호출됨
void UMySystemSingleton::OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
{
	My_LOGCALLF(Log_Frame, Log);

	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnWorldCleanup(World, bSessionEnded, bCleanupResources);
	}
}

// World 정리 완료후 호출됨
void UMySystemSingleton::OnPostWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
{
	My_LOGCALLF(Log_Frame, Log);

	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnPostWorldCleanup(World, bSessionEnded, bCleanupResources);
	}
}

// World 생성후 호출됨
void UMySystemSingleton::OnPostWorldCreation(UWorld* World)
{
	My_LOGCALLF(Log_Frame, Log);
	
	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnPostWorldCreation(World);
	}
}

// World 초기화 전 호출됨
void UMySystemSingleton::OnPrevWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS)
{
	My_LOGCALLF(Log_Frame, Log);

	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnPrevWorldInitialization(World, IVS);
	}
}

// World 초기화 후 호출됨
void UMySystemSingleton::OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS)
{
	My_LOGCALLF(Log_Frame, Log);

	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnPostWorldInitialization(World, IVS);
	}
}

// World 소멸시 호출됨 (초기화 된 World 에서만 호출)
void UMySystemSingleton::OnPrevWorldFinishDestroy(UWorld* World)
{
	My_LOGCALLF(Log_Frame, Log);

	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnPrevWorldFinishDestroy(World);
	}
}

// UWorld::AddToWorld() 함수로 Level이 추가 될때 호출됨.
//	- FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject();
void UMySystemSingleton::OnLevelAddedToWorld(ULevel* Level, UWorld* World)
{
	My_LOGF(Log_Frame, Log, TEXT("Level Name : %s"), *Level->GetName() );
	
	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnLevelAddedToWorld(Level, World);
	}
}

// UWorld::RemoveFromWorld() 함수로 Level이 제거 될때 호출됨.
//	- FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject();
void UMySystemSingleton::OnLevelRemovedFromWorld(ULevel* Level, UWorld* World)
{
	My_LOGF(Log_Frame, Log, TEXT("Level Name : %s"), *Level->GetName());
	
	// 이벤트 전달
	for (auto& mgr : MapManager)
	{
		UMyManagerBase* regMgr = Cast<UMyManagerBase>(mgr.Value);

		if (regMgr == nullptr) continue;
		if (regMgr->IsValidLowLevel() == false) continue;

		regMgr->OnLevelRemovedFromWorld(Level, World);
	}
}

#pragma endregion Event_Delegate

