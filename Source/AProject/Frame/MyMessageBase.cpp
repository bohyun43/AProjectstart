
// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMessageBase.h"
#include "MyManagerDef.h"



MyPacketBuffer::MyPacketBuffer() :
	m_chpBuffer(nullptr),
	m_chpDataFieldStart(nullptr),
	m_chpDataFieldEnd(nullptr),
	m_chpReadPos(nullptr),
	m_chpWritePos(nullptr)
{
	// ���� ����� �Է����� �ʴ´ٸ�, �⺻ġ�� ����.
	m_chpBuffer				= nullptr;
	m_chpBufferExpansion	= nullptr;

	Initial();
}

MyPacketBuffer::MyPacketBuffer(int iBufferSize) : 
	m_chpBuffer(nullptr),
	m_chpDataFieldStart(nullptr),
	m_chpDataFieldEnd(nullptr),
	m_chpReadPos(nullptr),
	m_chpWritePos(nullptr)
{
	m_chpBuffer				= nullptr;
	m_chpBufferExpansion	= nullptr;

	Initial(iBufferSize);
}

MyPacketBuffer::MyPacketBuffer(const MyPacketBuffer &SrcPacket) :
	m_chpBuffer(nullptr),
	m_iBufferSize(0),
	m_chpDataFieldStart(nullptr),
	m_chpDataFieldEnd(nullptr),
	m_chpReadPos(nullptr),
	m_chpWritePos(nullptr)
{
	m_chpBuffer				= nullptr;
	m_chpBufferExpansion	= nullptr;

	Initial(SrcPacket.m_iBufferSize);

	// ���� ��Ŷ Ŭ�������� �����ؿ´�.
	WriteData(SrcPacket.m_chpReadPos, SrcPacket.m_iDataSize);
}

MyPacketBuffer::~MyPacketBuffer()
{
	Release();
}

// ��Ŷ �ʱ�ȭ.
void MyPacketBuffer::Initial(uint32 iBufferSize)
{
	m_iBufferSize = iBufferSize;

	if (m_chpBuffer == nullptr)
	{
		if (MSG_PACKET_BUFFER_MAX < m_iBufferSize)
		{
			// �⺻ ũ�⺸�� Ŭ ���
			m_chpBufferExpansion	= new uint8[m_iBufferSize];
			m_chpBuffer				= m_chpBufferExpansion;
		}
		else
		{
			m_chpBufferExpansion	= nullptr;
			m_chpBuffer				= m_chaBufferDefault;
		}
	}

	My_CHECK(m_chpBuffer);

	m_chpDataFieldStart = m_chpBuffer;
	m_chpDataFieldEnd	= m_chpBuffer + m_iBufferSize;

	m_chpReadPos = m_chpWritePos = m_chpDataFieldStart;
	m_iDataSize  = 0;
}


// ��Ŷ  �ı�.
void MyPacketBuffer::Release(void)
{
	if ( m_chpBufferExpansion !=  nullptr )
		SAFE_DELETE_ARRAY( m_chpBufferExpansion );
}

// ��Ŷ û��.
void MyPacketBuffer::Clear(void)
{
	My_CHECK(m_chpBuffer);

	m_chpDataFieldStart = m_chpBuffer;
	m_chpDataFieldEnd	= m_chpBuffer + m_iBufferSize;

	m_chpReadPos = m_chpWritePos = m_chpDataFieldStart;
	m_iDataSize = 0;
}


// ���� Pos �̵�. (�����̵��� �ȵ�)
//	- GetBufferPtr �Լ��� �̿��Ͽ� �ܺο��� ������ ���� ������ ������ ��� ���. 
//	- Parameters	: (int) �̵� ������.
//	- Return		: (int) �̵��� ������.
uint32 MyPacketBuffer::MoveWritePos(uint32 iSize)
{
	if (0 > iSize) return 0;

	// �̵��� �ڸ��� �����ϴٸ�.
	if (m_chpWritePos + iSize > m_chpDataFieldEnd)
		return 0;

	m_chpWritePos += iSize;
	m_iDataSize	  += iSize;

	return iSize;
}

// ���� Pos �̵�. (�����̵��� �ȵ�)
//	- GetBufferPtr �Լ��� �̿��Ͽ� �ܺο��� ������ ���� ������ ������ ��� ���. 
//	- Parameters	: (int) �̵� ������.
//	- Return		: (int)�̵��� ������.
uint32 MyPacketBuffer::MoveReadPos(uint32 iSize)
{
	if (0 > iSize) return 0;

	// �̵��Ҹ�ŭ ����Ÿ�� ���ٸ�.
	if (iSize > m_iDataSize)
		return 0;

	m_chpReadPos += iSize;
	m_iDataSize  -= iSize;

	return iSize;
}

//-----------------------------------------------------------------------
// ������ ���۷�����.
//-----------------------------------------------------------------------
MyPacketBuffer &MyPacketBuffer::operator = (MyPacketBuffer &cSrcAyaPacket)
{
	m_chpReadPos  = m_chpBuffer;
	m_chpWritePos = m_chpBuffer;

	// ���� ��Ŷ Ŭ�������� �����ؿ´�.
	WriteData(cSrcAyaPacket.m_chpReadPos, cSrcAyaPacket.m_iDataSize);

	return *this;
}


// ����Ÿ ���.
//	- Parameters: (char *)Dest ������. (int)Size.
//	-  Return	: (int)������ ������.
uint32 MyPacketBuffer::ReadData(uint8 *chpDest, uint32 iSize)
{
	// ����� �ϴ� ��ŭ�� ����Ÿ�� ���ٸ�.
	if (iSize > m_iDataSize)
		return 0;

	FMemory::Memcpy(chpDest, m_chpReadPos, iSize);

	m_chpReadPos += iSize;
	m_iDataSize	 -= iSize;

	return iSize;
}

// ����Ÿ ����.
//	- Parameters: (char *)Src ������. (int)SrcSize.
//	- Return	: (int)������ ������.
uint32 MyPacketBuffer::WriteData(uint8 *chpSrc, uint32 iSrcSize)
{
	// ���� �ڸ��� ���ٸ�.
	if (m_chpWritePos + iSrcSize > m_chpDataFieldEnd)
		return 0;

	FMemory::Memcpy(m_chpWritePos, chpSrc, iSrcSize);

	m_chpWritePos	+= iSrcSize;
	m_iDataSize		+= iSrcSize;

	return iSrcSize;
}

//------------------------------------------------------------------------
MyMessageBase::MyMessageBase()
{
	SetHeader(0);
	SetType(EMessageType::Msg_None);

	m_iPacketSize = 0;
}

MyMessageBase::~MyMessageBase()
{

}

// ��Ŷ ��ü �б�
uint32 MyMessageBase::ReadPacket(uint8 *chpDest, uint32 iSize)
{
	m_iPacketSize = iSize;

	return ReadData(chpDest, iSize);
}

// �б� ��ġ�� ������ ���� ���� ���ϴ� ������ ��ġ���� ������ �б�.
MyPacketHeader MyMessageBase::GetHeaderData()
{
	MyPacketHeader header;
	FMemory::Memcpy((uint8*)&header, m_chpDataFieldStart, sizeof(MyPacketHeader));
	return header;
}

// ������ �б�/���� �غ�
void MyMessageBase::SeekMessage(ESeekType type)
{
	m_chpReadPos = m_chpWritePos = m_chpDataFieldStart;

	switch (type)
	{
	case ESeekType::Read:
		// �б��� ���
		m_chpReadPos	+= sizeof(MyPacketHeader);
		m_iDataSize		= m_iPacketSize - sizeof(MyPacketHeader);		// ������ ó�� ��ġ�� �̵�
		break;

	case ESeekType::Write:
		// ���� �� ���
		m_chpWritePos	+= sizeof(MyPacketHeader);
		m_iDataSize		= sizeof(MyPacketHeader);						// ������ ó�� ��ġ�� �̵�
		break;
	}
}

// UDP Network (Peer-Agent)
//------------------------------------------------------------------------
MyMessageHost::MyMessageHost()
{
	SetHeader(0);
	SetType(EMessageType::Msg_Host);
}

MyMessageHost::~MyMessageHost()
{

}


// TCP Network (TCP/WEB)
//------------------------------------------------------------------------
MyMessageServer::MyMessageServer()
{
	SetHeader(0);
	SetType(EMessageType::Msg_Server);
}

MyMessageServer::~MyMessageServer()
{

}


// Input (Keyboard, Mouse, Pad)
//------------------------------------------------------------------------
FSMessageInput::FSMessageInput()
{
	SetHeader(0);
	SetType(EMessageType::Msg_Input);
}

FSMessageInput::~FSMessageInput()
{

}


// Logic (GameLogic)
//------------------------------------------------------------------------
MyMessageLogic::MyMessageLogic()
{
	SetHeader(0);
	SetType(EMessageType::Msg_Logic);
}

MyMessageLogic::~MyMessageLogic()
{

}
