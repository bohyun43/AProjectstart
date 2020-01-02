// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Frame/MyManagerBase.h"
#include "MyTableDef.h"
#include "MyTableManager.generated.h"

/*
 테이블 읽기 및 저장 지원
	- DataTableSet	> Table(Excel:cvs) 지원
	- DataXmlSet	> Xml 지원
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
	virtual void FinishDestroy() override;		// UObject GC 해제

	virtual void ManagerInit() override;
	virtual void ManagerClear() override;

	virtual void ManagerStandBy() override;
	virtual void ManagerBegin() override;
	virtual void ManagerTick(float deltaTime) override;
	virtual void ManagerEnd() override;	


	// 형변환 지원 접근
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
	UPROPERTY(Transient)	// GC 연결을 하지 않을 경우 먼저 해제되는 상황이 발생할 수 있다.
	TMap<ETableSetType, class UMyTableSetBase*> m_Tables;
};
