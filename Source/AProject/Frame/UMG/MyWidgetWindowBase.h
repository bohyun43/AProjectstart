// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyWidgetBase.h"
#include "MyUMGDef.h"
//#include "MyInputDef.h"
#include "MyWidgetWindowBase.generated.h"


/*
 * 다이얼로그 관리를 위한 기본 클래스
 */
UCLASS()
class APROJECT_API UMyWidgetWindowBase : public UMyWidgetBase
{
	GENERATED_BODY()
	
public:
	UMyWidgetWindowBase(const FObjectInitializer& ObjectInitializer);

	// 종류
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DialogBase)
	EUMGWindowType DialogKindType;

	// 깊이 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DialogBase)
	EUMGWindowType DialogDepthType;


public:

	// 최기화/종료
	virtual void DialogInitialize(class UMyUMGManager* manager);
	virtual void DialogShutdown();

	// 최상위로 이동.
	virtual void DialogGotoTop();

	// 보이기/숨기기
	virtual void DialogHide();
	virtual void DialogShow();
	
protected:

	//virtual void InputCallable(EInputAction inputAction, UWidget* Comp, bool IsMouse = false) override;

	// 대화창 정보 수집.
	virtual void CollectionInfomation() override;
	
	// AddToViewport() 함수가 호출될 때 UI위젯을 생성/소멸 하기 위해 호출됨.
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
		
protected:

	class UMyUMGManager*			m_Manager;

};
