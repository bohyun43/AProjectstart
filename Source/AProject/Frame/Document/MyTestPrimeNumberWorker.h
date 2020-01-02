#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Object.h"

/*
	// ���� �ڵ�
	// ����� ������� ������ �迭 ����
	TArray<uint32> PrimeNumbers;

	// ���� �ڵ�
	// ��Ƽ �������� ĳ�� �� ���ִ� �ڵ��� ��ȯ�մϴ�.
	// �ʿ��� ���, ���� �Լ� MyTestPrimeNumberWorker::Shutdown() �� ����մϴ�.
	MyTestPrimeNumberWorker::JoyInit(PrimeNumbers, 50000, this);

*/

//~~~~~ Multi Threading ~~~
class APROJECT_API MyTestPrimeNumberWorker : public FRunnable
{
public:
	// �̱������� �����Ͽ�, ������ Thread�� ������ �����ϰ� �մϴ�.
	static  MyTestPrimeNumberWorker* Runnable;

	// �۾��ڸ� �����ϱ����� ������
	FRunnableThread* Thread;

	// �۾�������
	TArray<uint32>* PrimeNumbers;

	// ����� PlayerController
	APlayerController* ThePC;

	// ������ ������ ����, ������ ���� ī����
	FThreadSafeCounter StopTaskCounter;

	// ���� �Ҽ� ã�� ����
	int32 FindNextPrimeNumber();

private:
	int32				PrimesFoundCount;

public:

	int32				TotalPrimesToFind;

	// �Ϸ� �Ǵ�.
	bool IsFinished() const
	{
		return PrimesFoundCount >= TotalPrimesToFind;
	}

	//~~~ ������ �ٽ� �Լ� ~~~

	// ����/�Ҹ���
	MyTestPrimeNumberWorker(TArray<uint32>& TheArray, const int32 IN_PrimesToFindPerTick, APlayerController* IN_PC);
	virtual ~MyTestPrimeNumberWorker();

	// FRunnable �Լ�
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

	// �����尡 ����� �����ߴ��� Ȯ��.
	void EnsureCompletion();

	//~~~ ������ ���� �� ���� ~~~

	/*
		������ �� �۾��ڸ� ����(���� �׼���)���� �����մϴ�.
		�� �ڵ�� �� ���� �ϳ��� Prime Number ������ �� ������ �� �ֵ��� �մϴ�.
		�� �Լ��� ���� ������ �ν��Ͻ��� ���� �ڵ��� ��ȯ�մϴ�.
	*/
	static MyTestPrimeNumberWorker* JoyInit(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, APlayerController* IN_PC);

	// �����带 �����մϴ�. �����̹Ƿ� ���� ������ ���ؽ�Ʈ �ܺο��� ȣ�� �� �� �ֽ��ϴ�
	static void Shutdown();

	static bool IsThreadFinished();
};