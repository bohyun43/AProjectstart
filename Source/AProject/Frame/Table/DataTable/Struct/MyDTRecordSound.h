// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/DataTable.h"
//#include "Sound/MySoundDef.h"
#include "MyDTRecordSound.generated.h"

/*
 * 사운드 cvs 파일 레코드
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

	// 에디터 일경우만 설명 지원.
#if WITH_EDITOR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundTable)
	FString SoundDesc;
#endif

	// 직접 연결안함 (필요할 경우 메모리에 올리는 방식 사용함)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundTable)
	//TSoftObjectPtr<USoundCue> CoundCue;		// 지연 로드 애셋	

	// 생성자
	FMyDTRecordSound() {}

	// 할당자
	FMyDTRecordSound(FMyDTRecordSound const& Other)
	{
		*this = Other;
	}
};


