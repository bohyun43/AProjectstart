// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTestPrimeNumberWorker.h"


// 정적 변수 초기화.
MyTestPrimeNumberWorker* MyTestPrimeNumberWorker::Runnable = NULL;

MyTestPrimeNumberWorker::MyTestPrimeNumberWorker(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, APlayerController* IN_PC)
{
	// 데이터를 저장할 위치에 링크 
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
	// 시작하기 전의 초기 대기 시간입니다 . 
	FPlatformProcess::Sleep(0.03);

	// 소수를 잦을때 까지 유지 합니다.
	while (StopTaskCounter.GetValue() == 0 && !IsFinished())
	{
		PrimeNumbers->Add(FindNextPrimeNumber());
		PrimesFoundCount++;

		// Main Game Thread 로 증가 값 알림!

		// 여기서 UObject를 생성, 파기 또는 수정해서는 안됩니다. 
		// 모든 스레드가 완료된 후에 그런 종류의 작업을 수행합니다. 
		// 모든 계산은 스레드에서 수행 할 수 있으나, UObject의 실제 제작/수정은 메인 게임 스레드에서 수행해야합니다. 
		ThePC->ClientMessage(FString::FromInt(PrimeNumbers->Last()));
		
		// 스레드가 너무 많은 리소스를 사용하지 못하게 함 
		// FPlatformProcess::Sleep(0.01);
	}

	// MyTestPrimeNumberWorker::IsThreadFinished()를 보고있는 게임 스레드의 타이머에서 MyTestPrimeNumberWorker::Shutdown() 을 실행합니다.

	return 0;
}

// stop
void MyTestPrimeNumberWorker::Stop()
{
	StopTaskCounter.Increment();
}

MyTestPrimeNumberWorker* MyTestPrimeNumberWorker::JoyInit(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, APlayerController* IN_PC)
{
	// 멀티 스레딩 가능 플랫폼일 경우, 새로운 스레드 인스턴스 생생 
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
	// 마지막 값
	int32 TestPrime = PrimeNumbers->Last();
	bool NumIsPrime = false;

	// 소수 구하는 로직.
	while (NumIsPrime==false)
	{
		NumIsPrime = true;

		// Try Next Number
		TestPrime++;

		// Modulus from 2 to current number - 1 
		for (int32 b = 2; b < TestPrime; b++)
		{
			//---------------------------------------------------------------~~~~~~~~~~~~
			// 스레드가 너무 많은 리소스를 사용하지 못하게 함 
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