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
 * ���̾�α� ������ ���� �⺻ Ŭ����
 */
UCLASS()
class APROJECT_API UMyWidgetWindowBase : public UMyWidgetBase
{
	GENERATED_BODY()
	
public:
	UMyWidgetWindowBase(const FObjectInitializer& ObjectInitializer);

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DialogBase)
	EUMGWindowType DialogKindType;

	// ���� ��ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DialogBase)
	EUMGWindowType DialogDepthType;


public:

	// �ֱ�ȭ/����
	virtual void DialogInitialize(class UMyUMGManager* manager);
	virtual void DialogShutdown();

	// �ֻ����� �̵�.
	virtual void DialogGotoTop();

	// ���̱�/�����
	virtual void DialogHide();
	virtual void DialogShow();
	
protected:

	//virtual void InputCallable(EInputAction inputAction, UWidget* Comp, bool IsMouse = false) override;

	// ��ȭâ ���� ����.
	virtual void CollectionInfomation() override;
	
	// AddToViewport() �Լ��� ȣ��� �� UI������ ����/�Ҹ� �ϱ� ���� ȣ���.
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
		
protected:

	class UMyUMGManager*			m_Manager;

};
