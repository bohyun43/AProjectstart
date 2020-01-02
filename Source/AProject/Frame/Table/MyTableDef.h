#pragma once


// TableSetType
UENUM(BlueprintType)
enum class ETableSetType : uint8
{
	TT_None,
	TT_DataTable,
	TT_Xml,

	TT_Max
};

// DataTableType : UDataTable (TT_DataTable)
UENUM(BlueprintType)
enum class EDataTypeTable : uint8
{
	DTT_None,
	DTT_Template,
	DTT_Sound,
	DTT_Stage,
	
	DTT_Max,
};


// XmlFileType
UENUM(BlueprintType)
enum class EDataTypeXml : uint8
{
	DTX_None,
	DTX_GameConfig,
	DTX_Max,
};


#ifndef FSUTIL_TABLE_DEFINE
#define FSUTIL_TABLE_DEFINE

// Table Support Util Function
namespace FSUtil
{


}

#endif 


