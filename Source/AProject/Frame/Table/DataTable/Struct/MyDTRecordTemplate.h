#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "MyDTRecordTemplate.generated.h"

UENUM(BlueprintType)
enum class ETemplateEnum : uint8
{
	Enum_A,
	Enum_B,
	Enum_C,
	Enum_D,
	Enum_E,
	Enum_F,
	Enum_Max,
};

/**
	�ۺ� �׽�Ʈ csv ���� ���ڵ�
		- DataTableUtils::IsSupportedTableProperty()

	������ ���̺��� ���� Structure ����
		- Excel ���ϰ� ������ ���缭 ��������� ��. (Format ���� : �׼��� Field �̸��� �Ȱ��� ���� �ʿ�)
		- C++ â�� ���� �ȵ�.
*/
// FS DataTableRecord
USTRUCT(BlueprintType)
struct FMyDTRecordTemplate : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	ETemplateEnum TempEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	FName TempString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	int32 TempInt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	float TempFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	FName TempParsing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	TAssetPtr<UTexture> TempTexture;		// ���� �ε� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	TSoftObjectPtr<UDataTable> TempTable;	// ���� �ε� �ּ�

	// TArray (Value,Value,Value)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	TArray<FString> TempArray;

	// TMap ((Key,Value),(Key,Value))
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	TMap<int32, FString> TempMap;
	
	// ������ Import �� ó�� ����.
	virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override {};

	// ������
	FMyDTRecordTemplate() {}

	// �Ҵ���
	FMyDTRecordTemplate(FMyDTRecordTemplate const& Other)
	{
		*this = Other;
	}
};


