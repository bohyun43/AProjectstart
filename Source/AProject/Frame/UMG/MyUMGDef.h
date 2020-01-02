#pragma once

// 대화창 Depth
UENUM(BlueprintType)
enum class EUMGDepthType : uint8
{
	DDT_None,
	DDT_Top,		// 상단 (Ticker)
	DDT_Middle,		// 중단 (Popup) 
	DDT_Bottom,		// 하단 (Menu)
	DDT_Max
};

// 대화창 종류
UENUM(BlueprintType)
enum class EUMGWindowType : uint8
{
	DKT_None,
	DKT_Popup,
	DKT_Window,
	DKT_Max
};

struct FUMGEvent
{
	EUMGWindowType		typeKind;

	TWeakObjectPtr<class UWidget> target;
};


#ifndef FSUTIL_UMG_DEFINE
#define FSUTIL_UMG_DEFINE

// UMG Support Util Function
namespace FSUtil
{


}


#endif 