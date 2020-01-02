#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "MyType.h"
#include "MyDTTower.generated.h"

/**
	템블릿 테스트 csv 파일 레코드
		- DataTableUtils::IsSupportedTableProperty()

	데이터 테이블의 위한 Structure 구성
		- Excel 파일과 구성을 맞춰서 생성해줘야 함. (Format 구성 : 액셀의 Field 이름과 똑같이 구성 필요)
		- C++ 창에 노출 안됨.
*/
// FS DataTableRecord
USTRUCT(BlueprintType)
struct FMyDTTower : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
		ECardRule CardRule;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//FName TempString;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//int32 TempInt;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//float TempFloat;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//FName TempParsing;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//TAssetPtr<UTexture> TempTexture;		// 직접 로드 에셋

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//TSoftObjectPtr<UDataTable> TempTable;	// 지연 로드 애셋

	//// TArray (Value,Value,Value)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//TArray<FString> TempArray;

	//// TMap ((Key,Value),(Key,Value))
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//TMap<int32, FString> TempMap;
	
	// 데이터 Import 후 처리 지원.
	virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override {};

	// 생성자
	FMyDTTower() {}

	// 할당자
	FMyDTTower(FMyDTTower const& Other)
	{
		*this = Other;
	}
};


