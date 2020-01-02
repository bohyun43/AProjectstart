// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/DataTable.h"
//#include "Sound/MySoundDef.h"
#include "MyDTRecordSound.generated.h"

/*
 * ���� cvs ���� ���ڵ�
 */
 // FS DataTableRecord
USTRUCT(BlueprintType)
struct FMyDTRecordSound : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundTable)
	FString SoundName;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundTable)
	//ESoundType SoundType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundTable)
	FString SoundCueName;

	// ������ �ϰ�츸 ���� ����.
#if WITH_EDITOR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundTable)
	FString SoundDesc;
#endif

	// ���� ������� (�ʿ��� ��� �޸𸮿� �ø��� ��� �����)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundTable)
	//TSoftObjectPtr<USoundCue> CoundCue;		// ���� �ε� �ּ�	

	// ������
	FMyDTRecordSound() {}

	// �Ҵ���
	FMyDTRecordSound(FMyDTRecordSound const& Other)
	{
		*this = Other;
	}
};


