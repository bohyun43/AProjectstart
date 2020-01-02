// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUMGDef.h"
#include "MyWidgetBase.generated.h"

/**
 * UI ������ ���� �⺻ Ŭ����
 */
UCLASS()
class APROJECT_API UMyWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UMyWidgetBase(const FObjectInitializer& ObjectInitializer);

	// �̺�Ʈ ����
	UFUNCTION(BlueprintCallable, Category= "Dialog")
	void OnButtonClick(UWidget* targetComponent, bool IsMouse = false);

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void OnButtonHover(UWidget* targetComponent);

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void OnButtonNormal(UWidget* targetComponent);

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void OnButtonRelease(UWidget* targetComponent);

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void OnPushAnimation(UWidget* targetComponent);

public:

	virtual bool Initialize() override;
	virtual void Shutdown();


	#pragma region Support Widget Function

	UWidget* FindWidget(const FName& widgetName);

	void SetWidgetPosition(const FName& widgetName, FVector2D pos);
	void SetWidgetRotation(const FName& widgetName, float angle);
	void SetWidgetScale(const FName& widgetName, FVector2D scale);
	void SetWidgetShear(const FName& widgetName, FVector2D shear);
	void SetWidgetDepth(const FName& widgetName, const int32 zorder);
	void SetWidgetSize(const FName& widgetName, const FVector2D& size);

	FVector2D		GetWidgetSize(const FName& widgetName);
	FName			GetWidgetType(const FName& widgetName);

	#pragma endregion

	#pragma region Support Animation

	bool IsExistAnimation(const FName& animationName);

	bool PlayAnimation(const FName& animationName, float startTime = 0.0f, int32 loopCount = 1, EUMGSequencePlayMode::Type playType = EUMGSequencePlayMode::Forward);
	void StopAnimation(const FName& animationName);
	void PauseAnimation(const FName& animationName);

	void GetAnimations(OUT TArray<FName>& animationList);

	#pragma endregion


protected:

	// FSUI ���� �Ǵ�
	bool IsFSUIBase(const FName& fsuiName);

	// FSUI �˻�
	UMyWidgetBase* FindFSUIChild(const FName& fsuiName);
	

	//virtual void InputCallable(EInputAction inputAction, UWidget* Comp, bool IsMouse = false);

	// ��ȭâ ���� ����.
	virtual void CollectionInfomation();

	// AddToViewport() �Լ��� ȣ��� �� UI������ ����/�Ҹ� �ϱ� ���� ȣ���.
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
protected:

	TMap<FName, UWidget*>			m_IncludeWidgets;
	TMap<FName, UWidgetAnimation*>	m_IncludeAnimations;

	UWidgetBlueprintGeneratedClass*	m_BPClass;		// Blueprint Class
};
