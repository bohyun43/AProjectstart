#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "MyType.h"
#include "MyDTTower.generated.h"

/**
	�ۺ� �׽�Ʈ csv ���� ���ڵ�
		- DataTableUtils::IsSupportedTableProperty()

	������ ���̺��� ���� Structure ����
		- Excel ���ϰ� ������ ���缭 ��������� ��. (Format ���� : �׼��� Field �̸��� �Ȱ��� ���� �ʿ�)
		- C++ â�� ���� �ȵ�.
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
	//TAssetPtr<UTexture> TempTexture;		// ���� �ε� ����

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//TSoftObjectPtr<UDataTable> TempTable;	// ���� �ε� �ּ�

	//// TArray (Value,Value,Value)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//TArray<FString> TempArray;

	//// TMap ((Key,Value),(Key,Value))
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TemplateTable)
	//TMap<int32, FString> TempMap;
	
	// ������ Import �� ó�� ����.
	virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override {};

	// ������
	FMyDTTower() {}

	// �Ҵ���
	FMyDTTower(FMyDTTower const& Other)
	{
		*this = Other;
	}
};


