#pragma once


UENUM(BlueprintType)
enum class EMessageType : uint8
{
	Msg_None,
	Msg_Host,		// Host(Peer/Agent)
	Msg_Server,		// Server(TCP/Web)
	Msg_Input,		// Keyboard/Mouse
	Msg_Logic,		// Logic
	Mgr_Max
};

#pragma pack(push, 1)
struct MyPacketHeader
{
	union
	{
		struct
		{
			uint8			msgType;		// uint8	(EMessageType)
			uint8			msgEx1;			// uint8
			uint16			msgEx2;			// uint16

			uint16			msgCmd;			// uint16
			uint16			msgSize;		// uint16
			
		};
		uint32  msgUnique[2];
		uint64	msgHeader;
	};
};
#pragma pack(pop)


#define		MSG_PACKET_HEADER_SIZE		sizeof(MyPacketHeader)
#define		MSG_PACKET_BUFFER_MAX		1024

// PacketBase
//------------------------------------------------------------------------
class MyPacketBuffer
{
	/*---------------------------------------------------------------
	- ���� : ť�� �ƴϹǷ�, �ֱ�(<<). ����(>>) �� ȥ���ؼ� ����ϸ� �ȵȴ�.

	Write
	PacBuf << (uint32)40030;	or	PacBuf << iValue;		(uint32 �ֱ�)
	PacBuf << (uint8)3;			or	PacBuf << byValue;		(uint8  �ֱ�)
	PacBuf << (float)1.4;		or	PacBuf << fValue;		(float  �ֱ�)

	Read
	PacBuf >> iValue;		(int   ����)
	PacBuf >> byValue;		(BYTE  ����)
	PacBuf >> fValue;		(float ����)
	----------------------------------------------------------------*/

public:

	MyPacketBuffer();
	MyPacketBuffer(int iBufferSize);
	MyPacketBuffer(const MyPacketBuffer &SrcPacket);

	virtual	~MyPacketBuffer();

	// ��Ŷ �ʱ�ȭ.
	void	Initial(uint32 iBufferSize = MSG_PACKET_BUFFER_MAX);
	
	// ��Ŷ �ı�.
	void	Release(void);

	// ��Ŷ û��.
	void	Clear(void);

	// ���� ������ ���.
	uint32	GetBufferSize(void) { return m_iBufferSize; }

	// ���� ������� ������ ���.
	uint32	GetDataSize(void) { return m_iDataSize; }

	// ���� ������ ���.
	uint8*	GetBufferPtr(void) { return m_chpBuffer; }

	// ���� Pos �̵�. (�����̵��� �ȵ�)
	//	- GetBufferPtr �Լ��� �̿��Ͽ� �ܺο��� ������ ���� ������ ������ ��� ���. 
	//	- Parameters	: (int) �̵� ������. 
	//	- Return		: (int) �̵��� ������.
	uint32	MoveWritePos(uint32 iSize);
	uint32	MoveReadPos(uint32 iSize);


	//------------------------------------------------------------
	// ������ ���۷�����.
	//------------------------------------------------------------
	MyPacketBuffer	&operator = (MyPacketBuffer &srcPacket);

	// Write/Push.	�� ���� Ÿ�Ը��� ��� ����.
	MyPacketBuffer	&operator << (int8 iValue)		{ WriteData(reinterpret_cast<uint8 *>(&iValue), sizeof(int8));		return *this; }		// signed
	MyPacketBuffer	&operator << (int16 iValue)		{ WriteData(reinterpret_cast<uint8 *>(&iValue), sizeof(int16));		return *this; }
	MyPacketBuffer	&operator << (int32 iValue)		{ WriteData(reinterpret_cast<uint8 *>(&iValue), sizeof(int32));		return *this; }
	MyPacketBuffer	&operator << (int64 iValue)		{ WriteData(reinterpret_cast<uint8 *>(&iValue), sizeof(int64));		return *this; }

	MyPacketBuffer	&operator << (uint8 iValue)		{ WriteData(reinterpret_cast<uint8 *>(&iValue), sizeof(uint8));		return *this; }		// unsigned
	MyPacketBuffer	&operator << (uint16 iValue)	{ WriteData(reinterpret_cast<uint8 *>(&iValue), sizeof(uint16));	return *this; }
	MyPacketBuffer	&operator << (uint32 iValue)	{ WriteData(reinterpret_cast<uint8 *>(&iValue), sizeof(uint32));	return *this; }
	MyPacketBuffer	&operator << (uint64 iValue)	{ WriteData(reinterpret_cast<uint8 *>(&iValue), sizeof(uint64));	return *this; }

	MyPacketBuffer	&operator << (DWORD dwValue)	{ WriteData(reinterpret_cast<uint8 *>(&dwValue), sizeof(DWORD));	return *this; }
	MyPacketBuffer	&operator << (float fValue)		{ WriteData(reinterpret_cast<uint8 *>(&fValue), sizeof(float));		return *this; }
	MyPacketBuffer	&operator << (double dValue)	{ WriteData(reinterpret_cast<uint8 *>(&dValue), sizeof(double));	return *this; }

	// Read/Pop.	�� ���� Ÿ�Ը��� ��� ����.
	MyPacketBuffer	&operator >> (int8  &iValue)	{ ReadData(reinterpret_cast<uint8 *>(&iValue), sizeof(int8));		return *this; }
	MyPacketBuffer	&operator >> (int16 &iValue)	{ ReadData(reinterpret_cast<uint8 *>(&iValue), sizeof(int16));		return *this; }
	MyPacketBuffer	&operator >> (int32 &iValue)	{ ReadData(reinterpret_cast<uint8 *>(&iValue), sizeof(int32));		return *this; }
	MyPacketBuffer	&operator >> (int64 &iValue)	{ ReadData(reinterpret_cast<uint8 *>(&iValue), sizeof(int64));		return *this; }
	
	MyPacketBuffer	&operator >> (uint8  &iValue)	{ ReadData(reinterpret_cast<uint8 *>(&iValue), sizeof(uint8));		return *this; }
	MyPacketBuffer	&operator >> (uint16 &iValue)	{ ReadData(reinterpret_cast<uint8 *>(&iValue), sizeof(uint16));		return *this; }
	MyPacketBuffer	&operator >> (uint32 &iValue)	{ ReadData(reinterpret_cast<uint8 *>(&iValue), sizeof(uint32));		return *this; }
	MyPacketBuffer	&operator >> (uint64 &iValue)	{ ReadData(reinterpret_cast<uint8 *>(&iValue), sizeof(uint64));		return *this; }

	MyPacketBuffer	&operator >> (DWORD &dwValue)	{ ReadData(reinterpret_cast<uint8 *>(&dwValue), sizeof(DWORD));		return *this; }
	MyPacketBuffer	&operator >> (float &fValue)	{ ReadData(reinterpret_cast<uint8 *>(&fValue), sizeof(float));		return *this; }
	MyPacketBuffer	&operator >> (double &dValue)	{ ReadData(reinterpret_cast<uint8 *>(&dValue), sizeof(double));		return *this; }


	// ����Ÿ ���.
	//------------------------------------------------------------
	// Parameters	: (char *)Dest ������. (int)Size.
	// Return		: (int)������ ������.
	uint32		ReadData(uint8 *chpDest, uint32 iSize);

	// ����Ÿ ����.
	//------------------------------------------------------------
	// Parameters	: (char *)Src ������. (int)SrcSize.
	// Return		: (int)������ ������.
	uint32		WriteData(uint8 *chpSrc, uint32 iSrcSize);
	
protected:
	
	
	//------------------------------------------------------------
	// ��Ŷ���� / ���� ������.
	//------------------------------------------------------------
	uint8	m_chaBufferDefault[MSG_PACKET_BUFFER_MAX];
	uint8*	m_chpBufferExpansion;

	uint8*	m_chpBuffer;
	uint32	m_iBufferSize;

	//------------------------------------------------------------
	// ��Ŷ���� ���� ��ġ.	(�� Ŭ���� ������ ������� ������, Ȯ�强�� ���� ���)
	//------------------------------------------------------------
	uint8*	m_chpDataFieldStart;
	uint8*	m_chpDataFieldEnd;

	//------------------------------------------------------------
	// ������ ���� ��ġ, ���� ��ġ.
	//------------------------------------------------------------
	uint8*	m_chpReadPos;
	uint8*	m_chpWritePos;

	//------------------------------------------------------------
	// ���� ���ۿ� ������� ������.
	//------------------------------------------------------------
	uint32	m_iDataSize;
};


/*
	�޼��� Class ���.
*/
class MyMessageBase : public MyPacketBuffer
{
public:

	enum ESeekType
	{
		Read,
		Write,
	};

	MyMessageBase();
	virtual ~MyMessageBase();
		
	uint64			GetHeader()						{ return ((MyPacketHeader*)m_chpBuffer)->msgHeader;  }
	void			SetHeader(uint64 in)			{ ((MyPacketHeader*)m_chpBuffer)->msgHeader = in; }

	EMessageType	GetType() 						{ return (EMessageType)((MyPacketHeader*)m_chpBuffer)->msgType; }
	void			SetType(EMessageType in)		{ ((MyPacketHeader*)m_chpBuffer)->msgType = (uint8)in; }

	uint16			GetCmd() 						{ return ((MyPacketHeader*)m_chpBuffer)->msgCmd; }
	void			SetCmd(uint16 in)				{ ((MyPacketHeader*)m_chpBuffer)->msgCmd = in; }

	uint16			GetSize() 						{ return ((MyPacketHeader*)m_chpBuffer)->msgSize; }
	void			SetSize(uint16 in)				{ ((MyPacketHeader*)m_chpBuffer)->msgSize = in; }

	uint8			GetEx1() 						{ return ((MyPacketHeader*)m_chpBuffer)->msgEx1; }
	void			SetEx1(uint8 in)				{ ((MyPacketHeader*)m_chpBuffer)->msgEx1 = in; }

	uint16			GetEx2()						{ return ((MyPacketHeader*)m_chpBuffer)->msgEx2; }
	void			SetEx2(uint16 in)				{ ((MyPacketHeader*)m_chpBuffer)->msgEx2 = in; }
		
	// ��Ŷ �б�
	uint32			ReadPacket(uint8 *chpDest, uint32 iSize);
	
	// �ش� �б�
	MyPacketHeader	GetHeaderData();

	// ������ �б�/���� �غ� (������ ��ġ�� �̵���)
	void			SeekMessage(ESeekType type);
	
protected:

	uint32			m_iPacketSize;
};

// UDP Network (Peer-Agent)
//------------------------------------------------------------------------
class MyMessageHost : public MyMessageBase
{
public:
	MyMessageHost();
	virtual ~MyMessageHost();

	void Send(uint8* data, uint32 size)		{ WriteData(data, size); }
	void Recv(uint8* data, uint32 size)		{ ReadData(data, size); }

protected:
};

// TCP Network (TCP/WEB)
//------------------------------------------------------------------------
class MyMessageServer : public MyMessageBase
{
public:
	MyMessageServer();
	virtual ~MyMessageServer();

	void Send(uint8* data, uint32 size)		{ WriteData(data, size); }
	void Recv(uint8* data, uint32 size)		{ ReadData(data, size); }

protected:
};

// Input (Keyboard, Mouse, Pad)
//------------------------------------------------------------------------
class FSMessageInput : public MyMessageBase
{
public:
	FSMessageInput();
	virtual ~FSMessageInput();

	void Push(uint8* data, uint32 size)		{ WriteData(data, size); }
	void Pop (uint8* data, uint32 size)		{ ReadData(data, size); }

protected:

};

// Logic (GameLogic)
//------------------------------------------------------------------------
class MyMessageLogic : public MyMessageBase
{
public:
	MyMessageLogic();
	virtual ~MyMessageLogic();

	void Push(uint8* data, uint32 size)		{ WriteData(data, size); }
	void Pop(uint8* data, uint32 size)		{ ReadData(data, size); }

protected:
};





