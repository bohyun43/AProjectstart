#pragma once

// STL 
#include <time.h>
#include <assert.h>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)					{ if(p) { delete (p);     (p)=nullptr; } }
#endif 

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)			{ if(p) { delete [] (p);  (p)=nullptr; } }
#endif 


// Bit Flag
#define BIT_SET(flag, option)			(flag |= option)
#define BIT_REMOVE(flag, option)		(flag &= ~option)
#define BIT_TOGGLE(flag, option)		(flag ^= option)
#define BIT_CHECK(flag, option)			((flag & option) != 0)

#define BIT_CHECK_uint8(flag, option)	(((uint8)flag & (uint8)option) != 0)

// Log
DECLARE_LOG_CATEGORY_EXTERN(Log_Base, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Log_Frame, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Log_Print, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(Log_Lua, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Log_Logic, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Log_Event, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Log_UI, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Log_Server, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Log_Data, Log, All);

// Log On:1/Off:0 적용
#define Use_Log_Base		1	// Constructor / Destroy flow display
#define Use_Log_Frame		1	// FrameWorkd flow display
#define Use_Log_Print		1	// Test Output display

#define Use_Log_Lua			1
#define Use_Log_Logic		1
#define Use_Log_Event		1
#define Use_Log_UI			1
#define Use_Log_Server		1
#define Use_Log_Data		1

#define My_LOGFUNC							(FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__)+ TEXT(")"))

#define My_LOGCALL(Category, Verb)			if (Use_##Category) UE_LOG(Category, Verb)
#define My_LOGCALLF(Category, Verb)			if (Use_##Category) UE_LOG(Category, Verb, TEXT("%s"), *My_LOGFUNC)

#define My_LOG(Category, Verb,Format, ...)	if (Use_##Category) UE_LOG(Category, Verb, TEXT("%s"), *FString::Printf(Format, ##__VA_ARGS__ ))
#define My_LOGF(Category, Verb,Format, ...)	if (Use_##Category) UE_LOG(Category, Verb, TEXT("%s %s"), *My_LOGFUNC, *FString::Printf(Format, ##__VA_ARGS__ ))
#define My_PRINT(Format, ...)				if (Use_Log_Print)  UE_LOG(Log_Print, Display, TEXT("%s"), *FString::Printf(Format, ##__VA_ARGS__ ))

#define My_CHECK(Expr, ...) \
{ \
	if(!(Expr)) \
	{ \
		My_LOGF(Log_Frame, Error, TEXT("[Check Failed] : %s"), TEXT(""#Expr"")); \
		return __VA_ARGS__; \
	} \
}

#define My_PRINTSCREEN(Color, Format, ...)	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, Color, FString::Printf(Format, ##__VA_ARGS__ ))

// SET_WARN_COLOR(COLOR_CYAN); CLEAR_WARN_COLOR(); 지원 안됨.
#define My_TRACE(Category, Format, ...) \
{ \
	const FString msg = FString::Printf(Format,  ##__VA_ARGS__ ); \
	if (Use_##Category) \
		UE_LOG(Category, Log, TEXT("%s %s %s"), *My_LOGFUNC, *msg, *GetNameSafe(this)); \
}

UENUM(BlueprintType)
enum class EManagerType : uint8
{
	Mgr_None,
	Mgr_Config,
	Mgr_Lua,
	Mgr_Table,
	Mgr_EnemySpawn,
	Mgr_Input,
	Mgr_Stream,			// 애셋 로딩 및 로딩 포멧 지원
	Mgr_Camera,
	Mgr_Spawn,			// Spawn : Actor 생성
	Mgr_State,			// State : FSM
	Mgr_Level,			// Map
	Mgr_UMG,			// 2D UMG
	Mgr_Sound,
	Mgr_Network,	
	Mgr_Max
};


// #include Define
#include "MyManagerMacro.h"
#include "MyMessageBase.h"
#include "MyMessageStruct.h"

#include "Enum/MyEnum_Regist.h"
//#include "Lua/MyEnumLua_Call.h"
//#include "Lua/MyEnumLua_Glue.h"

//#include "Camera/MyCameraDef.h"
#include "UMG/MyUMGDef.h"
//#include "Input/MyInputDef.h"
//#include "Network/MyNetworkDef.h"
//#include "Sound/MySoundDef.h"
//#include "State/MyStateDef.h"
//#include "Stream/MyStreamingDef.h"
#include "Table/MyTableDef.h"


#ifndef MyUTIL_MANAGER_DEFINE
#define MyUTIL_MANAGER_DEFINE

// Manager Support Util Function
namespace MyUtil
{
	// StaticLoadObject
	//-----------------------------------------------------------------------------
	template <typename T>
	static FORCEINLINE T* LoadObjectFromPath(const FString& path)
	{
		if (path.IsEmpty())
			return nullptr;
							    
		return Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *path));
	}

	template <typename T>
	static FORCEINLINE T* LoadObjectFromPath(const TCHAR* path)
	{
		if (path.IsEmpty())
			return nullptr;

		return Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, path));
	}

	// Enum <> String(Name) 변환
	//-----------------------------------------------------------------------------
	template< typename T>
	static FORCEINLINE FString EnumToString(const FString& enumName, const T value)
	{
		UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName);
		return *(pEnum ? pEnum->GetNameStringByIndex(static_cast<uint8>(value)) : "Invalid");
	}

	template <typename T>
	static FORCEINLINE T NameToEnum(const FString& enumName, FName value)
	{
		T enumState = 0;
		UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName);
		if (pEnum != nullptr)
		{	
			int32 index = pEnum->GetIndexByName(value);
			enumState = (T)static_cast<uint8>(index);
		}
		return enumState;
	}

	template <typename T>
	static FORCEINLINE T StringToEnum(const FString& enumName, FString value)
	{
		T enumState = (T)0;
		UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName);
		if (pEnum != nullptr)
		{
			int32 index = pEnum->GetIndexByNameString(value);
			enumState = (T)static_cast<uint8>(index);
		}
		return enumState;
	}
};

#endif 
