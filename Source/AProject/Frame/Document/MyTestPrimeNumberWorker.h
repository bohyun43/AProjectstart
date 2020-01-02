#pragma once

//#include "Engine.h"
#include "EngineMinimal.h"
#include "Object.h"

/*
	// 선언 코드
	// 헤더에 만들어질 데이터 배열 생성
	TArray<uint32> PrimeNumbers;

	// 구현 코드
	// 멀티 스레딩은 캐시 될 수있는 핸들을 반환합니다.
	// 필요한 경우, 정적 함수 MyTestPrimeNumberWorker::Shutdown() 을 사용합니다.
	MyTestPrimeNumberWorker::JoyInit(PrimeNumbers, 50000, this);

*/

//~~~~~ Multi Threading ~~~
class APROJECT_API MyTestPrimeNumberWorker : public FRunnable
{
public:
	// 싱글톤으로 선언하여, 언제든 Thread에 접근이 용이하게 합니다.
	static  MyTestPrimeNumberWorker* Runnable;

	// 작업자를 실행하기위한 스레드
	FRunnableThread* Thread;

	// 작업데이터
	TArray<uint32>* PrimeNumbers;

	// 사용할 PlayerController
	APlayerController* ThePC;

	// 스레드 중지를 위한, 스레드 안전 카운터
	FThreadSafeCounter StopTaskCounter;

	// 실제 소수 찾는 로직
	int32 FindNextPrimeNumber();

private:
	int32				PrimesFoundCount;

public:

	int32				TotalPrimesToFind;

	// 완료 판단.
	bool IsFinished() const
	{
		return PrimesFoundCount >= TotalPrimesToFind;
	}

	//~~~ 스레드 핵심 함수 ~~~

	// 생성/소멸자
	MyTestPrimeNumberWorker(TArray<uint32>& TheArray, const int32 IN_PrimesToFindPerTick, APlayerController* IN_PC);
	virtual ~MyTestPrimeNumberWorker();

	// FRunnable 함수
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

	// 스레드가 제대로 정지했는지 확인.
	void EnsureCompletion();

	//~~~ 스레드 시작 및 중지 ~~~

	/*
		스레드 및 작업자를 정적(쉬운 액세스)으로 실행합니다.
		이 코드는 한 번에 하나의 Prime Number 스레드 만 실행할 수 있도록 합니다.
		이 함수는 새로 시작한 인스턴스에 대한 핸들을 반환합니다.
	*/
	static MyTestPrimeNumberWorker* JoyInit(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, APlayerController* IN_PC);

	// 스레드를 종료합니다. 정적이므로 쉽게 스레드 컨텍스트 외부에서 호출 할 수 있습니다
	static void Shutdown();

	static bool IsThreadFinished();
};