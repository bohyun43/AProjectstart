// Fill out your copyright notice in the Description page of Project Settings.

#include "MyManagerBase.h"


UMyManagerBase::UMyManagerBase()
{
	//My_LOGCALLF(Log_Base, Log); 
	ManagerType = EManagerType::Mgr_None;

	m_IsEnable = false;
	m_IsUpdate = true;
}

void UMyManagerBase::ManagerInit()	
{
	//My_LOGCALLF(Log_Frame, Log); 
}

void UMyManagerBase::ManagerClear()
{
	//My_LOGCALLF(Log_Frame, Log);
}

void UMyManagerBase::ManagerStandBy()
{
	//My_LOGCALLF(Log_Frame, Log);
}

void UMyManagerBase::ManagerBegin()
{
	//My_LOGCALLF(Log_Frame, Log);
}

void UMyManagerBase::ManagerTick(float deltaTime)
{
	//My_LOGCALLF(Log_Frame, Log);
}

void UMyManagerBase::ManagerEnd()
{
	//My_LOGCALLF(Log_Frame, Log);
}

void UMyManagerBase::ProcessMessage(MyMessageBase* msg)
{
	//My_LOGCALLF(Log_Frame, Log);
}

// GetClass() vs StaticClass() 차이
void UMyManagerBase::GetClassVsStaticClass()
{
	// 디버그 모드
#if WITH_EDITOR

	UMyManagerBase* newManager = NewObject<UMyManagerBase>(this, TEXT("TestUObject"));

	UClass* UObjectClass						= newManager->GetClass();
	UClass* UObjectStaticClass					= UMyManagerBase::StaticClass();
	UClass* UObjectStaticClassTakenFromGetClass = newManager->GetClass()->StaticClass();

	UE_LOG(Log_Frame, Log, TEXT("newManager->GetClass(): %s"),					*newManager->GetClass()->GetName());
	UE_LOG(Log_Frame, Log, TEXT("newManager::StaticClass(): %s"),				*UMyManagerBase::StaticClass()->GetName());
	UE_LOG(Log_Frame, Log, TEXT("newManager->GetClass()->StaticClass(): %s"),	*newManager->GetClass()->StaticClass()->GetName());

	bool Test1 = false;
	if (newManager->IsA(newManager->GetClass()))
	{
		Test1 = true;
	}
	UE_LOG(Log_Frame, Log, TEXT("newManager->IsA(newManager->GetClass() result is: %s"), Test1 ? TEXT("True") : TEXT("False"));


	bool Test2 = false;
	if (newManager->IsA(UMyManagerBase::StaticClass()))
	{
		Test2 = true;
	}
	UE_LOG(Log_Frame, Log, TEXT("newManager->IsA(UMyManagerBase::StaticClass()) result is: %s"), Test2 ? TEXT("True") : TEXT("False"));

	bool Test3 = false;
	if (newManager->IsA(newManager->GetClass()->StaticClass()))
	{
		Test3 = true;
	}
	UE_LOG(Log_Frame, Log, TEXT("newManager->GetClass()->StaticClass()) result is: %s"), Test3 ? TEXT("True") : TEXT("False"));

#endif
}