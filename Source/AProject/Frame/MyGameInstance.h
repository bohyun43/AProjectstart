// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/*
	App�� �����ϱ� ���� �뵵�� GameInstance�� �����Ѵ�.

	- App ���� ���� ����.
	- ���� Status�� �̰����� �����ϸ�, App�� �ʱ�ȭ �ɶ� �����͸� �о���̰� App�� ����ɶ� ���� �����ʹ� �����ȴ�.
	- ���� : [������Ʈ ����] > [������Ʈ - ��&���] > GameInstance ���.

	[���� ���� �帧]
		> [�� �ʱ�ȭ]					UGameInstance::Init()
		> [������ ���� ������Ʈ �ʱ�ȭ]	AActorComponent::InitializeComponent()
		> [������ ���� ������ �ʱ�ȭ]	AActor::PostInitializeComponents()
		> [�÷��̾��� �α���]			AGameMode::PostLogin()
		> [������ ����]					AGameMode::StartPlay(), AActor::BeginPlay()
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
	// Editor�� Play/Simulate ���� �ʱ�ȭ ȣ���.
	virtual FGameInstancePIEResult InitializeForPlayInEditor(int32 PIEInstanceIndex, const FGameInstancePIEParameters& Params) override;

	// Editor�� Play/Simulate ���� ���� ȣ���.
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
