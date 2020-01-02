// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDebugWidgetBase.h"

UMyDebugWidgetBase::UMyDebugWidgetBase(const FObjectInitializer& ObjectInitializer) : UMyWidgetBase(ObjectInitializer)
{

}


void UMyDebugWidgetBase::SetLeftTime(int8 Time)
{
	if (LefeTimeTextBlock == nullptr)
	{
		return;
	}

	if (LeftTime == Time)
	{
		return;
	}

	LeftTime = Time;

	FString Temp = FString::Printf(TEXT("%d초 남았습니다."), LeftTime);
	LefeTimeTextBlock->SetText(FText::FromString(Temp));
}

bool UMyDebugWidgetBase::Initialize()
{
	Super::Initialize();

	LeftTime = 0;
	return true;
}

void UMyDebugWidgetBase::NativeConstruct()
{
	LefeTimeTextBlock = Cast< UTextBlock>(GetWidgetFromName(TEXT("LeftTime")));

}
