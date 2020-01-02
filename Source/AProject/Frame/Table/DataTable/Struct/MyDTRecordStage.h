// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/DataTable.h"
//#include "Sound/MySoundDef.h"
#include "MyDTRecordStage.generated.h"

/*
 * Stage cvs 파일 레코드 (맵 스테이지)
 */
 // FS DataTableRecord
USTRUCT(BlueprintType)
struct FMyDTRecordStage : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// 장면 구성 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	TArray<FString> StagePath;

	// 장면 구성 군중
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	TArray<FString> AudiencePath;

	// 사용 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	bool bEnable;
	
	// TimeOfDay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	int32 TimeOfDay;
	
	// Weather
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	int32 Weather;
	

	// 생성자
	FMyDTRecordStage() {}

	// 할당자
	FMyDTRecordStage(FMyDTRecordStage const& Other)
	{
		*this = Other;
	}
};


