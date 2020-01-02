// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Frame/Table/MyTableSetBase.h"
#include "MyDataTableSet.generated.h"

/**
 UDatatable ���� ����
	- FTableRowBase ��� �޴� Struct Code ���� (Editor Do not Support )
	- Compile > Editor Start
	- cvs ���� ��� �� ����ü ���� (Google Spreadsheets �� ���� CSV ���Ϸ� ���)
 */
UCLASS(Blueprintable, BlueprintType)
class APROJECT_API UMyDataTableSet : public UMyTableSetBase
{
	GENERATED_BODY()
	
public:
	UMyDataTableSet();
		
	// Wrapper
	virtual void FinishDestroy() override;		// UObject GC ����

	virtual void TableInit(class UMyTableManager* parent) override;
	virtual void TableRelease() override;
	
	virtual bool TableLoad() override;
	virtual bool TableSave() override;

	virtual void TableBegin() override;
	virtual void TableEnd()	 override;
	

	// ����ȯ ���� ����
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
	UDataTable* GetTable(EDataTypeTable tableType);				// ���̺� ����

	UFUNCTION(BlueprintCallable, Category = DataTable)
	bool		HasTable(const EDataTypeTable tableType);		// ���̺� Ȯ��

protected:

	// DataTable Registry (Editor ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataTable, Meta = (AllowPrivateAccess = true))
	TMap<EDataTypeTable, class UDataTable*> DataTableSet;
	

	// GC�� ���� ������ �����ϱ� ���� ó��.
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

	// ����ȯ ���� ����
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


	UDataTable* GetTableHolder(EDataTypeTable tableType);			// ���̺� Ȧ�� ����
	bool		LoadTableHolder(EDataTypeTable tableType, FString assetName);
	bool		HasTableHolder(const EDataTypeTable tableType);		// ���̺� Ȧ�� Ȯ��

protected:
	// PROPERTY()�� ���� ���� ���� ��� GC�� ���ϱ� ���� Holder�� ����. (����� ����)
	TMap<EDataTypeTable, MyDataTableHolder*> DataTableHolder;
};
