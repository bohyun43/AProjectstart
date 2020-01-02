
#if (!defined(ENUM_Protocol_H) || defined(IMPLEMENT_FSEnum_Strings))

#if( !defined(IMPLEMENT_FSEnum_Strings) )
#define ENUM_Protocol_H
#endif

#include "MyEnumToString.h"

ENUM_BEGIN_TYPE(EProtocol, uint16)

	ENUM_ELEMENT(EProtocol, AAA)					// 테스트
	ENUM_ELEMENT(EProtocol, BBB)
	ENUM_ELEMENT_EQUAL(EProtocol, CCC, 1000)
	ENUM_ELEMENT_EQUAL(EProtocol, DDD, CCC + 1000)
	ENUM_ELEMENT(EProtocol, EEE)
	// 테스트.
	ENUM_ELEMENT(EProtocol, FFF)
	ENUM_ELEMENT_END(EProtocol, GGG)

ENUM_END_TYPE(EProtocol, uint16)


#endif // ( !defined(ENUM_Protocol_H) || defined(IMPLEMENT_FSEnum_Strings) )
