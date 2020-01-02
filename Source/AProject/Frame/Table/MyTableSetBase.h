// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyManagerDef.h"
#include "MyTableDef.h"
#include "MyTableSetBase.generated.h"

/*
 * Table ������ ���� ���� ����� �ٸ��� �ϱ� ���� ��� Ŭ����
 */
UCLASS()
class APROJECT_API UMyTableSetBase : public UObject
{
	GENERATED_BODY()

public:
	UMyTableSetBase();
	
	virtual void TableInit(class UMyTableManager* parent) { m_pManager = parent; }
	virtual void TableRelease()								{}

	virtual bool TableLoad()	{ return true; }
	virtual bool TableSave()	{ return true; }

	virtual void TableBegin()	{}
	virtual void TableEnd()		{}

protected:
		
	class UMyTableManager* m_pManager;
};
