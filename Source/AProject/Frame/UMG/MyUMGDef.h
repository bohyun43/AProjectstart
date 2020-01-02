#pragma once

// ��ȭâ Depth
UENUM(BlueprintType)
enum class EUMGDepthType : uint8
{
	DDT_None,
	DDT_Top,		// ��� (Ticker)
	DDT_Middle,		// �ߴ� (Popup) 
	DDT_Bottom,		// �ϴ� (Menu)
	DDT_Max
};

// ��ȭâ ����
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