// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Frame/UMG/MyWidgetBase.h"
#include "MyDebugWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UMyDebugWidgetBase : public UMyWidgetBase
{
	GENERATED_BODY()
public:
	UMyDebugWidgetBase(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTextBlock* LefeTimeTextBlock;

	UPROPERTY()
		uint8 LeftTime;

	void SetLeftTime(int8 Time);

public:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
};
