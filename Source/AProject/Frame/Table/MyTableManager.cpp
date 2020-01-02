// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTableManager.h"
#include "MyTableSetBase.h"

// Set
#include "Table/DataTable/MyDataTableSet.h"


UMyTableManager::UMyTableManager()
{
	My_LOGCALLF(Log_Base, Log);

	ManagerType = EManagerType::Mgr_Table;

	// �⺻ Ŭ���� ���
	TablesRegistry.Add(ETableSetType::TT_DataTable, UMyDataTableSet::StaticClass());
	
	m_Tables.Empty();
}

void UMyTableManager::FinishDestroy()
{
	My_LOGCALLF(Log_Base, Log);
	Super::FinishDestroy();
}

void UMyTableManager::ManagerInit()
{
	My_LOGCALLF(Log_Frame, Log);
	Super::ManagerInit();

	// ��ϵ� Ŭ����(Override)�� �����Ѵ�.
	for (auto& tableset : TablesRegistry)
	{
		if (tableset.Value == nullptr)
			continue;

		UClass*	registClass = tableset.Value;

		if (registClass != nullptr && registClass->IsChildOf<UMyTableSetBase>() == true)
		{
			// ��ϵ� TableSet Class ����.
			UMyTableSetBase* pCreateTableSet = NewObject<UMyTableSetBase>(GetTransientPackage(), registClass, registClass->GetFName());
			if (pCreateTableSet == nullptr)
				continue;

			My_LOGF(Log_Frame, Log, TEXT("Create Table Set : %s"), *registClass->GetFName().ToString());

			m_Tables.Add(tableset.Key, pCreateTableSet);

			pCreateTableSet->TableInit(this);
		}
		else
		{
			My_LOGF(Log_Frame, Warning, TEXT("Skip TableSet : %s - Not IsChildOf<UMyTableSetBase>()"), *registClass->GetFName().ToString());
		}
	}
}

void UMyTableManager::ManagerClear()
{
	for (auto& tableset : m_Tables)
	{
		UMyDataTableSet* tableSet = Cast<UMyDataTableSet>(tableset.Value);

		if (tableSet == nullptr) continue;
		if (tableSet->IsValidLowLevel() == false) continue;

		tableSet->TableRelease();

		My_LOGF(Log_Frame, Log, TEXT("Delete Table Set : %s"), *tableSet->GetFName().ToString());

		// UObject �Ļ� Destroy
		tableSet->ConditionalBeginDestroy();
		tableSet = nullptr;
	}

	m_Tables.Empty();

	Super::ManagerClear();
	My_LOGCALLF(Log_Frame, Log);
}

void UMyTableManager::ManagerStandBy()
{
	My_LOGCALLF(Log_Frame, Log);
	Super::ManagerStandBy();
}

void UMyTableManager::ManagerBegin()
{
	My_LOGCALLF(Log_Frame, Log);
	Super::ManagerBegin();

	// ���̺� ������ ���� ��� BeginPlay()ȣ�� ��.
	for (auto& tableset : m_Tables)
	{
		UMyTableSetBase* tableSet = Cast<UMyTableSetBase>(tableset.Value);
		if (tableSet != nullptr)
		{
			tableSet->TableBegin();
		}
	}
}

void UMyTableManager::ManagerTick(float deltaTime)
{
	Super::ManagerTick(deltaTime);
}

void UMyTableManager::ManagerEnd()
{
	for (auto& tableset : m_Tables)
	{
		UMyTableSetBase* tableSet = Cast<UMyTableSetBase>(tableset.Value);

		if (tableSet == nullptr) continue;
		if (tableSet->IsValidLowLevel() == false) continue;

		tableSet->TableEnd();
	}

	Super::ManagerEnd();
	My_LOGCALLF(Log_Frame, Log);
}
