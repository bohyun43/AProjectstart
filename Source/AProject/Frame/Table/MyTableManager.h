// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Frame/MyManagerBase.h"
#include "MyTableDef.h"
#include "MyTableManager.generated.h"

/*
 ���̺� �б� �� ���� ����
	- DataTableSet	> Table(Excel:cvs) ����
	- DataXmlSet	> Xml ����
 */


UCLASS(Blueprintable, BlueprintType)
class APROJECT_API UMyTableManager : public UMyManagerBase
{
	GENERATED_BODY()

public:

	UMyTableManager();
	
	// TableSet Registry
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TableManager)
	TMap<ETableSetType, TSubclassOf<class UMyTableSetBase>> TablesRegistry;


	// Override
	virtual void FinishDestroy() override;		// UObject GC ����

	virtual void ManagerInit() override;
	virtual void ManagerClear() override;

	virtual void ManagerStandBy() override;
	virtual void ManagerBegin() override;
	virtual void ManagerTick(float deltaTime) override;
	virtual void ManagerEnd() override;	


	// ����ȯ ���� ����
	template <typename T>
	T* GetTableSet(ETableSetType tableType)
	{
		T* returnValue = nullptr;

		if (m_Tables.Contains(tableType) == true)
		{
			return static_cast<T*>(m_Tables[tableType]);
		}
		return nullptr;
	}
	
protected:
	UPROPERTY(Transient)	// GC ������ ���� ���� ��� ���� �����Ǵ� ��Ȳ�� �߻��� �� �ִ�.
	TMap<ETableSetType, class UMyTableSetBase*> m_Tables;
};
