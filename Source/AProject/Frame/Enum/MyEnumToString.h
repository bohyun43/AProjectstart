
#undef ENUM_ELEMENT
#undef ENUM_ELEMENT_EQUAL
#undef ENUM_ELEMENT_END
#undef ENUM_ELEMENT_END_EQUAL
#undef ENUM_BEGIN
#undef ENUM_END
#undef ENUM_BEGIN_TYPE
#undef ENUM_END_TYPE

#ifdef IMPLEMENT_FSEnum_Strings

	// Implement (Base)
	//#define ENUM_ELEMENT(Ele_)						TEXT(#Ele_)
	//#define ENUM_BEGIN(EnumName)						FString gs_##EnumName [] = 
	//#define ENUM_END(EnumName)						; FString GetString##EnumName(enum tag##EnumName index) { return gs_##EnumName[index]; }

	#if WITH_EDITOR
		// Implement (TMap Extend)
		#define ENUM_ELEMENT(Enum_,Ele_)						gs_##Enum_.Add( static_cast<int32>(Ele_), TEXT(#Ele_) );
		#define ENUM_ELEMENT_EQUAL(Enum_,Ele_,Equ_)				ENUM_ELEMENT(Enum_,Ele_)
		#define ENUM_ELEMENT_END(Enum_,Ele_)					ENUM_ELEMENT(Enum_,Ele_)
		#define ENUM_ELEMENT_END_EQUAL(Enum_,Ele_,Equ_)			ENUM_ELEMENT(Enum_,Ele_)
		#define ENUM_BEGIN(Enum_)								TMap<int32, FString> gs_##Enum_; FString GetString##Enum_(int32 index) { if (gs_##Enum_.Num() == 0) {
		#define ENUM_END(Enum_)									} return gs_##Enum_.Find(index) != nullptr ? gs_##Enum_[index] : FString::Printf(TEXT("UnKnown")); }
		#define ENUM_BEGIN_TYPE(Enum_, Type_)					TMap<Type_, FString> gs_##Enum_; FString GetString##Enum_(Type_ index) { if (gs_##Enum_.Num() == 0) {
		#define ENUM_END_TYPE(Enum_, Type_)						} return gs_##Enum_.Find(index) != nullptr ? gs_##Enum_[index] : FString::Printf(TEXT("UnKnown")); }

	#else
		// Ignore
		#define ENUM_ELEMENT(Enum_,Ele_)					
		#define ENUM_ELEMENT_EQUAL(Enum_,Ele_,Equ_)			
		#define ENUM_ELEMENT_END(Enum_,Ele_)				
		#define ENUM_ELEMENT_END_EQUAL(Enum_,Ele_,Equ_)		
		#define ENUM_BEGIN(Enum_)						
		#define ENUM_END(Enum_)				
		#define ENUM_BEGIN_TYPE(Enum_, Type_)	
		#define ENUM_END_TYPE(Enum_, Type_)		
	#endif

#else // DECLARE_ENUM

	// declare (Base)
	//#define ENUM_ELEMENT(Ele_)						Ele_
	//#define ENUM_BEGIN(EnumName)						typedef enum tag##EnumName	
	//#define ENUM_END(EnumName)						EnumName; FString GetString##EnumName(enum tag##EnumName index);

	// declare (TMap Extend)
	#if WITH_EDITOR
		// declare (support GetString?)
		#define ENUM_ELEMENT(Enum_,Ele_)						Ele_,
		#define ENUM_ELEMENT_EQUAL(Enum_,Ele_, Equ_)			Ele_ = Equ_,
		#define ENUM_ELEMENT_END(Enum_,Ele_)					Ele_
		#define ENUM_ELEMENT_END_EQUAL(Enum_, Ele_, Equ_)		Ele_ = Equ_
		#define ENUM_BEGIN(Enum_)								typedef enum tag##Enum_ {	
		#define ENUM_END(Enum_)									} Enum_; FString GetString##Enum_(int32 index);
		#define ENUM_BEGIN_TYPE(Enum_, Type_)					typedef enum tag##Enum_ : Type_ {	
		#define ENUM_END_TYPE(Enum_, Type_)						} Enum_; FString GetString##Enum_(Type_ index);

	#else
		// declare 
		#define ENUM_ELEMENT(Enum_,Ele_)						Ele_,
		#define ENUM_ELEMENT_EQUAL(Enum_,Ele_, Equ_)			Ele_ = Equ_,
		#define ENUM_ELEMENT_END(Enum_,Ele_)					Ele_
		#define ENUM_ELEMENT_END_EQUAL(Enum_, Ele_, Equ_)		Ele_ = Equ_
		#define ENUM_BEGIN(Enum_)								typedef enum tag##Enum_ {	
		#define ENUM_END(Enum_)									} Enum_;
		#define ENUM_BEGIN_TYPE(Enum_, Type_)					typedef enum tag##Enum_ : Type_ {	
		#define ENUM_END_TYPE(Enum_, Type_)						} Enum_; 
	#endif

#endif
