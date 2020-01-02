// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/*
	App을 관리하기 위한 용도로 GameInstance를 지원한다.

	- App 관리 로직 지원.
	- 게임 Status를 이곳에서 관리하면, App이 초기화 될때 데이터를 읽어들이고 App이 종료될때 까지 데이터는 보존된다.
	- 적용 : [프로젝트 설정] > [프로젝트 - 맵&모드] > GameInstance 등록.

	[게임 시작 흐름]
		> [앱 초기화]					UGameInstance::Init()
		> [레벨에 속한 컴포넌트 초기화]	AActorComponent::InitializeComponent()
		> [레벨에 속한 액터의 초기화]	AActor::PostInitializeComponents()
		> [플레이어의 로그인]			AGameMode::PostLogin()
		> [게임의 시작]					AGameMode::StartPlay(), AActor::BeginPlay()
 */
UCLASS()
class APROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();
	

	// Override
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

	
	#if WITH_EDITOR
	// Editor상 Play/Simulate 게임 초기화 호출됨.
	virtual FGameInstancePIEResult InitializeForPlayInEditor(int32 PIEInstanceIndex, const FGameInstancePIEParameters& Params) override;

	// Editor상 Play/Simulate 게임 시작 호출됨.
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
	#endif
	
	// Access
	class UMySystemSingleton* GetFrameWork();
		
	
protected:
	
	void FrameInit();
	void FrameDrop();
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameSystem, meta = (AllowPrivateAccess = "true"))
	class UMySystemSingleton* FrameWork;

};
