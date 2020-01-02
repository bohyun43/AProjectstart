
#if( !defined(ENUM_Main_H) || defined(IMPLEMENT_FSEnum_Strings) )

#if( !defined(IMPLEMENT_FSEnum_Strings) )
#define ENUM_Main_H
#endif

#include "MyEnumToString.h"

ENUM_BEGIN(EMain)

	ENUM_ELEMENT(EMain, PM_LOGIC_START)					// �׽�Ʈ
	ENUM_ELEMENT(EMain, PM_CHAR_MSG_START)
	ENUM_ELEMENT_EQUAL(EMain, PM_STATE_CHANGE, 1000)
	ENUM_ELEMENT(EMain, STATE_CHAR_LOSEBALL_CHANGE)
	ENUM_ELEMENT(EMain, STATE_CHAR_ATTACKBALL_CHANGE)
	// �׽�Ʈ.
	ENUM_ELEMENT(EMain, STATE_CHAR_DEFENCE_CHANGE)
	ENUM_ELEMENT_END(EMain, STATE_CHAR_OFFECNE_CHANGE)

ENUM_END(EMain)


#endif // ( !defined(ENUM_Main_H) || defined(IMPLEMENT_FSEnum_Strings) )