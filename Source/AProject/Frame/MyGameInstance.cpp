
// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "MySystemSingleton.h"


UMyGameInstance::UMyGameInstance()
{
	My_LOGCALLF(Log_Base, Log);

	FrameWork = nullptr;
}

void UMyGameInstance::Init()
{
	My_LOGCALLF(Log_Frame, Log);

	Super::Init(); 

	FrameInit();	
}

void UMyGameInstance::Shutdown()
{
	FrameDrop();

	Super::Shutdown();

	My_LOGCALLF(Log_Frame, Log);
}

void UMyGameInstance::StartGameInstance()
{
	My_LOGCALLF(Log_Frame, Log);

	Super::StartGameInstance();
}

#if WITH_EDITOR
FGameInstancePIEResult UMyGameInstance::InitializeForPlayInEditor(int32 PIEInstanceIndex, const FGameInstancePIEParameters& Params)
{
	My_LOGCALLF(Log_Frame, Log);

	FGameInstancePIEResult result = Super::InitializeForPlayInEditor(PIEInstanceIndex, Params);

	return result;
}

FGameInstancePIEResult UMyGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	My_LOGCALLF(Log_Frame, Log);

	FGameInstancePIEResult result = Super::StartPlayInEditorGameInstance(LocalPlayer, Params);

	return result;
}
#endif


UMySystemSingleton* UMyGameInstance::GetFrameWork() { return FrameWork; }


void UMyGameInstance::FrameInit()
{
	My_LOGCALLF(Log_Frame, Log);

	if (GEngine->GameSingleton != nullptr)
	{
		FrameWork = Cast<UMySystemSingleton>(GEngine->GameSingleton);

		if (FrameWork != nullptr)
		{
			if (GetFrameWork() != nullptr)
				GetFrameWork()->SystemInit(this);
		}
		else
		{
			My_LOGF(Log_Frame, Warning, TEXT("FSSingleton Cast Failed"));
		}
	}
	else
	{
		My_LOGF(Log_Frame, Warning, TEXT("GEngine->GameSingleton == nullptr"));
	}
}

void UMyGameInstance::FrameDrop()
{
	if (GetFrameWork() != nullptr)
		GetFrameWork()->SystemDrop();

	FrameWork = nullptr;

	My_LOGCALLF(Log_Frame, Log);
}

