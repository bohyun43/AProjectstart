#pragma once

//#include "MyInputDef.h"

// UDP Network (Peer-Agent)
//------------------------------------------------------------------------




// TCP Network (TCP/WEB)
//------------------------------------------------------------------------




// Input (Keyboard, Mouse, Pad)
//------------------------------------------------------------------------
struct FSInputStruct
{
public:
	int32			inputID;			// ControllerID
	//EInputType		InputType;
	uint8			InputKey;
	//EInputAction	InputAction;
	float			Variation;

	FSInputStruct() {}
};



// Logic (GameLogic)
//------------------------------------------------------------------------