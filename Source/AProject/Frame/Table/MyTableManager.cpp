// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTableManager.h"
#include "MyTableSetBase.h"

// Set
#include "Table/DataTable/MyDataTableSet.h"


UMyTableManager::UMyTableManager()
{
	My_LOGCALLF(Log_Base, Log);

	ManagerType = EManagerType::Mgr_Table;

	// 기본 클래스 등록
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

	// 등록된 클래스(Override)를 생성한다.
	for (auto& tableset : TablesRegistry)
	{
		if (tableset.Value == nullptr)
			continue;

		UClass*	registClass = tableset.Value;

		if (registClass != nullptr && registClass->IsChildOf<UMyTableSetBase>() == true)
		{
			// 등록된 TableSet Class 생성.
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

		// UObject 파생 Destroy
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

	// 테이블 종류에 따라 모두 BeginPlay()호출 함.
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
