// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWidgetBase.h"

#include "UMG/Public/UMG.h"
#include "UMG/Public/UMGStyle.h"
#include "UMG/Public/Slate/SObjectWidget.h"
#include "UMG/Public/Blueprint/UserWidget.h"

UMyWidgetBase::UMyWidgetBase(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	m_BPClass = nullptr;

	m_IncludeWidgets.Empty();
	m_IncludeAnimations.Empty();
}

// 클릭 이벤트 발생
void UMyWidgetBase::OnButtonClick(UWidget* targetComponent, bool IsMouse /*= false*/)
{
	//if (targetComponent != nullptr)
	//	InputCallable(EInputAction::IAT_CLICK, targetComponent, IsMouse);
}

void UMyWidgetBase::OnButtonHover(UWidget* targetComponent)
{
	//if (targetComponent != nullptr)
	//	InputCallable(EInputAction::IAT_HOVER, targetComponent);
}

void UMyWidgetBase::OnButtonNormal(UWidget* targetComponent)
{
	//if (targetComponent != nullptr)
	//	InputCallable(EInputAction::IAT_NORMAL, targetComponent);
}

void UMyWidgetBase::OnButtonRelease(UWidget* targetComponent)
{
	//if (targetComponent != nullptr)
	//	InputCallable(EInputAction::IAT_RELEASE, targetComponent);
}

void UMyWidgetBase::OnPushAnimation(UWidget* targetComponent)
{

}


bool UMyWidgetBase::Initialize()
{
	if (UUserWidget::Initialize() == false)
		return false;

	CollectionInfomation();

	return true;
}

void UMyWidgetBase::Shutdown()
{

}

//-----------------------------------------------------------------------------------
// Support Widget Function
//-----------------------------------------------------------------------------------
UWidget* UMyWidgetBase::FindWidget(const FName& widgetName)
{
	FString widgetString = widgetName.ToString();
	FString widgetParent, widgetChild;

	if (widgetString.Split(TEXT("/"), &widgetParent, &widgetChild))
	{


	}

	return m_IncludeWidgets.FindRef(widgetName);
}

void UMyWidgetBase::SetWidgetPosition(const FName& widgetName, FVector2D pos)
{

}

void UMyWidgetBase::SetWidgetRotation(const FName& widgetName, float angle)
{

}

void UMyWidgetBase::SetWidgetScale(const FName& widgetName, FVector2D scale)
{

}

void UMyWidgetBase::SetWidgetShear(const FName& widgetName, FVector2D shear)
{

}

void UMyWidgetBase::SetWidgetDepth(const FName& widgetName, const int32 zorder)
{

}

void UMyWidgetBase::SetWidgetSize(const FName& widgetName, const FVector2D& size)
{

}

FVector2D UMyWidgetBase::GetWidgetSize(const FName& widgetName)
{
	return FVector2D::ZeroVector;
}

FName UMyWidgetBase::GetWidgetType(const FName& widgetName)
{
	return FName(TEXT(""));
}

bool UMyWidgetBase::IsFSUIBase(const FName& fsuiName)
{
	UWidget* widget = FindWidget(fsuiName);
	if (widget != nullptr && widget->IsValidLowLevel() == true)
	{
		FName widgetTypeName = GetWidgetType(fsuiName);
		
		if (widget->IsA(UMyWidgetBase::StaticClass()) == true)
			return true;
	}
	return false;
}

UMyWidgetBase* UMyWidgetBase::FindFSUIChild(const FName& fsuiName)
{
	return nullptr;
}


//-----------------------------------------------------------------------------------
// Support Animation
//-----------------------------------------------------------------------------------
bool UMyWidgetBase::IsExistAnimation(const FName& animationName)
{
	return true;
}

bool UMyWidgetBase::PlayAnimation(const FName& animationName, float startTime, int32 loopCount, EUMGSequencePlayMode::Type playType)
{
	FString animString = animationName.ToString();
	FString parentAnim, childAnim;

	if (animString.Split(TEXT("/"), &parentAnim, &childAnim))
	{
		UMyWidgetBase*  uiChild = FindFSUIChild(*parentAnim);
		if (uiChild != nullptr)
		{
			return uiChild->PlayAnimation(*childAnim, startTime, loopCount, playType);
		}
	}

	UWidgetAnimation* widgetAnim = m_IncludeAnimations.FindRef(animationName);
	if (widgetAnim != nullptr)
	{
		UUserWidget::PlayAnimation(widgetAnim, startTime, loopCount, playType);
		return true;
	}

	return false;
}

void UMyWidgetBase::StopAnimation(const FName& animationName)
{

}

void UMyWidgetBase::PauseAnimation(const FName& animationName)
{

}

void UMyWidgetBase::GetAnimations(OUT TArray<FName>& animationList)
{

}

// 전체 이벤트 통로
//void UMyWidgetBase::InputCallable(EInputAction inputAction, UWidget* Comp, bool IsMouse /*= false*/)
//{
//	if (GetWorld() == nullptr || GetWorld()->GetAuthGameMode() == nullptr)
//		return;
//
//	AGameModeBase* pGameMode = GetWorld()->GetAuthGameMode();
//	if (pGameMode == nullptr)
//		return;
//
//	//UGDTGameInstance* GameInst = Cast<UGDTGameInstance>(pGameMode->GetGameInstance());
//	//if (GameInst != nullptr)
//	//{
//	//	FDialogEvent msgInfo;
//	//	msgInfo.type	   = DialogType;
//	//	msgInfo.typeEvent  = EventType;
//
//	//	GameInst->Call_UIEvent(msgInfo);
//	//}
//}

void UMyWidgetBase::CollectionInfomation()
{
	// Blueprint Class 얻기.
	//m_BPClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
	//if (m_BPClass == nullptr)
	//	return;

	//// Animation 등록.
	//m_IncludeAnimations.Empty();

	//for (auto& anim : m_BPClass->Animations)
	//{
	//	UWidgetAnimation* animation = anim;

	//	if (animation != nullptr)
	//	{
	//		FString animString = animation->MovieScene->GetName();
	//		m_IncludeAnimations.Add( FName(*animString), animation );
	//	}
	//}

	//// Widget 등록.
	//m_IncludeWidgets.Empty();

	//TArray<UWidget*> allComponents;
	//if (WidgetTree != nullptr)
	//{
	//	WidgetTree->GetAllWidgets(allComponents);
	//}

	//for (auto& comp : allComponents)
	//{
	//	UWidget* widget = comp;
	//	if (widget == nullptr || widget->IsValidLowLevel() == false)
	//		continue;

	//	// Widget 수집
	//	FString  widgetString = widget->GetName();
	//	m_IncludeWidgets.Add(FName(*widgetString), widget);

	//	// Button Widget 콜백 함수 연결.
	//	if (widget->IsA(UButton::StaticClass()))
	//	{
	//		UButton* button = Cast<UButton>(widget);
	//		if (button != nullptr)
	//		{
	//			//button->OnPressed
	//		}
	//	}

	//}
}


void UMyWidgetBase::NativeConstruct()
{
	UUserWidget::NativeConstruct();
}

void UMyWidgetBase::NativeDestruct()
{
	UUserWidget::NativeConstruct();
}

