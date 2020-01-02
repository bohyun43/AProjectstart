// Fill out your copyright notice in the Description page of Project Settings.

#include "MyWidgetWindowBase.h"

#include "MyUMGDef.h"
#include "MyUMGManager.h"


UMyWidgetWindowBase::UMyWidgetWindowBase(const FObjectInitializer& ObjectInitializer) : UMyWidgetBase(ObjectInitializer)
{
	m_Manager = nullptr;
}

void UMyWidgetWindowBase::DialogInitialize(UMyUMGManager* manager)
{
	if (manager != nullptr)
		m_Manager = manager;

	CollectionInfomation();
}

void UMyWidgetWindowBase::DialogShutdown()
{
	
}

void UMyWidgetWindowBase::DialogGotoTop()
{

}

void UMyWidgetWindowBase::DialogHide()
{

}

void UMyWidgetWindowBase::DialogShow()
{

}



//void UMyWidgetWindowBase::InputCallable(EInputAction inputAction, UWidget* Comp, bool IsMouse /*= false*/)
//{
//	UMyWidgetBase::InputCallable(inputAction, Comp, IsMouse);
//}

void UMyWidgetWindowBase::CollectionInfomation()
{
	UMyWidgetBase::CollectionInfomation();
}

void UMyWidgetWindowBase::NativeConstruct()
{
	UMyWidgetBase::NativeConstruct();
}

void UMyWidgetWindowBase::NativeDestruct()
{
	UMyWidgetBase::NativeDestruct();
}
