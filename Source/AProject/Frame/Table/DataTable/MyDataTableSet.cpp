// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDataTableSet.h"
#include "MyTableSetBase.h"
#include "Engine/DataTable.h"		// UDataTable 지원

// DataTable Test...
#include "MyTableManager.h"
#include "Struct/MyDTRecordTemplate.h"
#include "Struct/MyDTRecordSound.h"
#include "Struct/MyDTRecordStage.h"


UMyDataTableSet::UMyDataTableSet()
{
	My_LOGCALLF(Log_Base, Log);

	// 데이터 연결 방법 1 : 생성자에서 데이터 연결 처리 Example
	/*
	FString TemplateTablePath = TEXT("Game/Resources/Table/xxx.xxx");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Template(*TemplateTablePath);
	My_CHECK(DT_Template.Succeeded() == true);
	DataTableSet.Add(EDataTypeTable::DTT_Temp, DT_Template.Object);
	*/

	// 데이터 연결 방법 2 : Blueprint로 파생 클래스 생성하여 DataTableSet에 등록
}

void UMyDataTableSet::FinishDestroy()
{
	My_LOGCALLF(Log_Base, Log);
	Super::FinishDestroy();
}

void UMyDataTableSet::TableInit(class UMyTableManager* parent)
{
	My_LOGCALLF(Log_Frame, Log);
	Super::TableInit(parent);

	// Todo
}

void UMyDataTableSet::TableRelease()
{
	// Todo
	for (auto& tableHolder : DataTableHolder)
	{
		SAFE_DELETE(tableHolder.Value);
	}
	DataTableHolder.Empty();
	
	Super::TableRelease();
	My_LOGCALLF(Log_Frame, Log);
}

bool UMyDataTableSet::TableLoad()
{
	// LoadTableHolder();

	My_LOGCALLF(Log_Frame, Log);
	return true;
}

bool UMyDataTableSet::TableSave()
{
	My_LOGCALLF(Log_Frame, Log);
	return true;
}

void UMyDataTableSet::TableBegin()
{
	// DataTable Test...
	/*if (UFSBlueprintFuncLibrary::IsFrame() == true)
	{
		UMySystemSingleton* pFrame = FS_FRMAE();
		if (pFrame != nullptr)
		{
			UMyDataTableSet* dataTableSet = pFrame->GetTable()->GetTableSet<UMyDataTableSet>(ETableSetType::TT_DataTable);
			if (dataTableSet != nullptr)
			{
				int32 templateIndex = 1;
				FMyDTRecordTemplate* templateRecord = dataTableSet->GetTableRecord<FMyDTRecordTemplate>(EDataTypeTable::DTT_Template, templateIndex);
				if (templateRecord != nullptr)
				{
					My_LOG(Log_Print, Log, TEXT("UMyDataTableSet:BeginPlay() Template Table > %d %s"), templateIndex, *templateRecord->TempString.ToString())
				}

				int32 soundIndex = 2000;
				FMyDTRecordSound* soundRecord = dataTableSet->GetTableRecord<FMyDTRecordSound>(EDataTypeTable::DTT_Sound, soundIndex);
				if (soundRecord != nullptr)
				{
					My_LOG(Log_Print, Log, TEXT("UMyDataTableSet:BeginPlay() Sound Table > %d %s"), soundIndex, *soundRecord->SoundCueName)
				}
			}
		}
	}*/
}

void UMyDataTableSet::TableEnd()
{
	// Todo
}

// DataTable 접근
UDataTable* UMyDataTableSet::GetTable(EDataTypeTable tableType)
{
	UDataTable** findedElem = DataTableSet.Find(tableType);
	if (findedElem != nullptr)
	{
		UDataTable* dataTable = *findedElem;
		if (dataTable != nullptr)
		{
			return dataTable;
		}
	}
	return nullptr;
}

// DataTable 등록되어 있는지 판단.
bool UMyDataTableSet::HasTable(const EDataTypeTable tableType)
{
	return DataTableSet.Contains(tableType);
}

// DataTableHolder 접근
UDataTable* UMyDataTableSet::GetTableHolder(EDataTypeTable tableType)
{
	UDataTable* retValue = nullptr;

	UMyDataTableSet::MyDataTableHolder** findedElem = DataTableHolder.Find(tableType);
	if (findedElem != nullptr)
	{
		UMyDataTableSet::MyDataTableHolder* dataTableHolder = *findedElem;
		if (dataTableHolder != nullptr)
		{
			retValue = dataTableHolder->GetDataTable();
		}
	}
	return retValue;
}

// DataTableHolder에 등록되어 있는지 판단.
bool UMyDataTableSet::HasTableHolder(const EDataTypeTable tableType)
{
	return DataTableHolder.Contains(tableType);
}

// UDataTable을 Holder에 등록 하기
bool UMyDataTableSet::LoadTableHolder(EDataTypeTable tableType, FString assetName)
{
	// DataTable Asset 읽기.
	UDataTable* dataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *assetName));

	if (dataTable != nullptr)
	{
		if (DataTableHolder.Contains(tableType) == false)
		{
			DataTableHolder.Add(tableType, new UMyDataTableSet::MyDataTableHolder(dataTable));
			return true;
		}
	}
	return false;
}

