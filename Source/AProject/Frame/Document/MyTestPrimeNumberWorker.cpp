// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTestPrimeNumberWorker.h"


// ���� ���� �ʱ�ȭ.
MyTestPrimeNumberWorker* MyTestPrimeNumberWorker::Runnable = NULL;

MyTestPrimeNumberWorker::MyTestPrimeNumberWorker(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, APlayerController* IN_PC)
{
	// �����͸� ������ ��ġ�� ��ũ 
	PrimeNumbers = &TheArray;

	TotalPrimesToFind	= IN_TotalPrimesToFind;
	ThePC				= IN_PC;
	
	PrimesFoundCount	= 0;
	StopTaskCounter.Set(0);

	Thread = FRunnableThread::Create(this, TEXT("MyTestPrimeNumberWorker"), 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
}

MyTestPrimeNumberWorker::~MyTestPrimeNumberWorker()
{
	delete Thread;
	Thread = NULL;
}

//Init
bool MyTestPrimeNumberWorker::Init()
{
	//Init the Data 
	PrimeNumbers->Empty();
	PrimeNumbers->Add(2);
	PrimeNumbers->Add(3);

	if (ThePC)
	{
		ThePC->ClientMessage("**********************************");
		ThePC->ClientMessage("Prime Number Thread Started!");
		ThePC->ClientMessage("**********************************");
	}
	return true;
}

//Run
uint32 MyTestPrimeNumberWorker::Run()
{
	// �����ϱ� ���� �ʱ� ��� �ð��Դϴ� . 
	FPlatformProcess::Sleep(0.03);

	// �Ҽ��� ������ ���� ���� �մϴ�.
	while (StopTaskCounter.GetValue() == 0 && !IsFinished())
	{
		PrimeNumbers->Add(FindNextPrimeNumber());
		PrimesFoundCount++;

		// Main Game Thread �� ���� �� �˸�!

		// ���⼭ UObject�� ����, �ı� �Ǵ� �����ؼ��� �ȵ˴ϴ�. 
		// ��� �����尡 �Ϸ�� �Ŀ� �׷� ������ �۾��� �����մϴ�. 
		// ��� ����� �����忡�� ���� �� �� ������, UObject�� ���� ����/������ ���� ���� �����忡�� �����ؾ��մϴ�. 
		ThePC->ClientMessage(FString::FromInt(PrimeNumbers->Last()));
		
		// �����尡 �ʹ� ���� ���ҽ��� ������� ���ϰ� �� 
		// FPlatformProcess::Sleep(0.01);
	}

	// MyTestPrimeNumberWorker::IsThreadFinished()�� �����ִ� ���� �������� Ÿ�̸ӿ��� MyTestPrimeNumberWorker::Shutdown() �� �����մϴ�.

	return 0;
}

// stop
void MyTestPrimeNumberWorker::Stop()
{
	StopTaskCounter.Increment();
}

MyTestPrimeNumberWorker* MyTestPrimeNumberWorker::JoyInit(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, APlayerController* IN_PC)
{
	// ��Ƽ ������ ���� �÷����� ���, ���ο� ������ �ν��Ͻ� ���� 
	//		and the platform supports multi threading!
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new MyTestPrimeNumberWorker(TheArray, IN_TotalPrimesToFind, IN_PC);
	}
	return Runnable;
}

void MyTestPrimeNumberWorker::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void MyTestPrimeNumberWorker::Shutdown()
{
	if (Runnable)
	{
		Runnable->EnsureCompletion();
		delete Runnable;
		Runnable = NULL;
	}
}

bool MyTestPrimeNumberWorker::IsThreadFinished()
{
	if (Runnable) 
		return Runnable->IsFinished();

	return true;
}

int32 MyTestPrimeNumberWorker::FindNextPrimeNumber()
{
	// ������ ��
	int32 TestPrime = PrimeNumbers->Last();
	bool NumIsPrime = false;

	// �Ҽ� ���ϴ� ����.
	while (NumIsPrime==false)
	{
		NumIsPrime = true;

		// Try Next Number
		TestPrime++;

		// Modulus from 2 to current number - 1 
		for (int32 b = 2; b < TestPrime; b++)
		{
			//---------------------------------------------------------------~~~~~~~~~~~~
			// �����尡 �ʹ� ���� ���ҽ��� ������� ���ϰ� �� 
			// FPlatformProcess::Sleep(0.01);
			//---------------------------------------------------------------~~~~~~~~~~~~

			if (TestPrime % b == 0)
			{
				NumIsPrime = false;
				break;				
			}
		}
	}

	//Success!
	return TestPrime;
}