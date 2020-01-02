// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Frame/Table/MyTableSetBase.h"
#include "MyDataTableSet.generated.h"

/**
 UDatatable 접근 지원
	- FTableRowBase 상속 받는 Struct Code 생성 (Editor Do not Support )
	- Compile > Editor Start
	- cvs 파일 등록 및 구조체 선택 (Google Spreadsheets 로 만들어서 CSV 파일로 출력)
 */
UCLASS(Blueprintable, BlueprintType)
class APROJECT_API UMyDataTableSet : public UMyTableSetBase
{
	GENERATED_BODY()
	
public:
	UMyDataTableSet();
		
	// Wrapper
	virtual void FinishDestroy() override;		// UObject GC 해제

	virtual void TableInit(class UMyTableManager* parent) override;
	virtual void TableRelease() override;
	
	virtual bool TableLoad() override;
	virtual bool TableSave() override;

	virtual void TableBegin() override;
	virtual void TableEnd()	 override;
	

	// 형변환 지원 접근
	template <typename T>
	T* GetTableRecord(EDataTypeTable tableType, FString rowName)
	{
		T* returnValue = nullptr;

		UDataTable* dataBase = GetTable(tableType);
		if (dataBase != nullptr)
		{
			returnValue = dataBase->FindRow<T>(*rowName, "", true /*Mission Log*/);
			return returnValue;
		}
		return nullptr;
	}

	template <typename T>
	T* GetTableRecord(EDataTypeTable tableType, int32 rowIndex)
	{
		return GetTableRecord<T>(tableType, FString::FromInt(rowIndex));
	}

	UFUNCTION(BlueprintCallable, Category = DataTable)
	UDataTable* GetTable(EDataTypeTable tableType);				// 테이블 접근

	UFUNCTION(BlueprintCallable, Category = DataTable)
	bool		HasTable(const EDataTypeTable tableType);		// 테이블 확인

protected:

	// DataTable Registry (Editor 관리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataTable, Meta = (AllowPrivateAccess = true))
	TMap<EDataTypeTable, class UDataTable*> DataTableSet;
	

	// GC에 의한 해제를 방지하기 위한 처리.
public:

	class MyDataTableHolder : public FGCObject
	{
	public:
		MyDataTableHolder(UDataTable* dataTable) : FGCObject(), m_pDataTableAsset(dataTable)
		{
			My_LOGCALLF(Log_Base, Log);
			My_CHECK(m_pDataTableAsset != nullptr);
		}

		virtual ~MyDataTableHolder(void)
		{
			My_LOGCALLF(Log_Base, Log);
		}

		virtual void AddReferencedObjects(FReferenceCollector& Collector) override
		{
			if (m_pDataTableAsset != nullptr)
			{
				Collector.AddReferencedObject(m_pDataTableAsset);
			}
		}

		UDataTable* GetDataTable() { return m_pDataTableAsset; }

	private:

		UDataTable* m_pDataTableAsset;

		// Do not call
		MyDataTableHolder() {};
	};

	// 형변환 지원 접근
	template <typename T>
	T* GetHolderRecord(EDataTypeTable tableType, FString rowName)
	{
		T* returnValue = nullptr;

		UDataTable* dataBase = GetTableHolder(tableType);
		if (dataBase != nullptr)
		{
			returnValue = dataBase->FindRow<T>(*rowName, "", true /*Mission Log*/);
			return returnValue;
		}
		return nullptr;
	}
	
	template <typename T>
	T* GetHolderRecord(EDataTypeTable tableType, int32 rowIndex)
	{
		return GetHolderRecord<T>(tableType, FString::FromInt(rowIndex));
	}


	UDataTable* GetTableHolder(EDataTypeTable tableType);			// 테이블 홀더 접근
	bool		LoadTableHolder(EDataTypeTable tableType, FString assetName);
	bool		HasTableHolder(const EDataTypeTable tableType);		// 테이블 홀더 확인

protected:
	// PROPERTY()로 연결 하지 않을 경우 GC를 피하기 위해 Holder로 연결. (사용자 관리)
	TMap<EDataTypeTable, MyDataTableHolder*> DataTableHolder;
};
