// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/DataTable.h"
//#include "Sound/MySoundDef.h"
#include "MyDTRecordStage.generated.h"

/*
 * Stage cvs ���� ���ڵ� (�� ��������)
 */
 // FS DataTableRecord
USTRUCT(BlueprintType)
struct FMyDTRecordStage : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// ��� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	TArray<FString> StagePath;

	// ��� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	TArray<FString> AudiencePath;

	// ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	bool bEnable;
	
	// TimeOfDay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	int32 TimeOfDay;
	
	// Weather
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageTable)
	int32 Weather;
	

	// ������
	FMyDTRecordStage() {}

	// �Ҵ���
	FMyDTRecordStage(FMyDTRecordStage const& Other)
	{
		*this = Other;
	}
};


