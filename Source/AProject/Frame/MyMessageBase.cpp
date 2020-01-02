
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
	// 버퍼 사이즈를 입력하지 않는다면, 기본치로 생성.
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

	// 원본 패킷 클래스에서 복사해온다.
	WriteData(SrcPacket.m_chpReadPos, SrcPacket.m_iDataSize);
}

MyPacketBuffer::~MyPacketBuffer()
{
	Release();
}

// 패킷 초기화.
void MyPacketBuffer::Initial(uint32 iBufferSize)
{
	m_iBufferSize = iBufferSize;

	if (m_chpBuffer == nullptr)
	{
		if (MSG_PACKET_BUFFER_MAX < m_iBufferSize)
		{
			// 기본 크기보다 클 경우
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


// 패킷  파괴.
void MyPacketBuffer::Release(void)
{
	if ( m_chpBufferExpansion !=  nullptr )
		SAFE_DELETE_ARRAY( m_chpBufferExpansion );
}

// 패킷 청소.
void MyPacketBuffer::Clear(void)
{
	My_CHECK(m_chpBuffer);

	m_chpDataFieldStart = m_chpBuffer;
	m_chpDataFieldEnd	= m_chpBuffer + m_iBufferSize;

	m_chpReadPos = m_chpWritePos = m_chpDataFieldStart;
	m_iDataSize = 0;
}


// 버퍼 Pos 이동. (음수이동은 안됨)
//	- GetBufferPtr 함수를 이용하여 외부에서 강제로 버퍼 내용을 수정할 경우 사용. 
//	- Parameters	: (int) 이동 사이즈.
//	- Return		: (int) 이동된 사이즈.
uint32 MyPacketBuffer::MoveWritePos(uint32 iSize)
{
	if (0 > iSize) return 0;

	// 이동할 자리가 부족하다면.
	if (m_chpWritePos + iSize > m_chpDataFieldEnd)
		return 0;

	m_chpWritePos += iSize;
	m_iDataSize	  += iSize;

	return iSize;
}

// 버퍼 Pos 이동. (음수이동은 안됨)
//	- GetBufferPtr 함수를 이용하여 외부에서 강제로 버퍼 내용을 수정할 경우 사용. 
//	- Parameters	: (int) 이동 사이즈.
//	- Return		: (int)이동된 사이즈.
uint32 MyPacketBuffer::MoveReadPos(uint32 iSize)
{
	if (0 > iSize) return 0;

	// 이동할만큼 데이타가 없다면.
	if (iSize > m_iDataSize)
		return 0;

	m_chpReadPos += iSize;
	m_iDataSize  -= iSize;

	return iSize;
}

//-----------------------------------------------------------------------
// 연산자 오퍼레이터.
//-----------------------------------------------------------------------
MyPacketBuffer &MyPacketBuffer::operator = (MyPacketBuffer &cSrcAyaPacket)
{
	m_chpReadPos  = m_chpBuffer;
	m_chpWritePos = m_chpBuffer;

	// 원본 패킷 클래스에서 복사해온다.
	WriteData(cSrcAyaPacket.m_chpReadPos, cSrcAyaPacket.m_iDataSize);

	return *this;
}


// 데이타 얻기.
//	- Parameters: (char *)Dest 포인터. (int)Size.
//	-  Return	: (int)복사한 사이즈.
uint32 MyPacketBuffer::ReadData(uint8 *chpDest, uint32 iSize)
{
	// 얻고자 하는 만큼의 데이타가 없다면.
	if (iSize > m_iDataSize)
		return 0;

	FMemory::Memcpy(chpDest, m_chpReadPos, iSize);

	m_chpReadPos += iSize;
	m_iDataSize	 -= iSize;

	return iSize;
}

// 데이타 삽입.
//	- Parameters: (char *)Src 포인터. (int)SrcSize.
//	- Return	: (int)복사한 사이즈.
uint32 MyPacketBuffer::WriteData(uint8 *chpSrc, uint32 iSrcSize)
{
	// 넣을 자리가 없다면.
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

// 패킷 전체 읽기
uint32 MyMessageBase::ReadPacket(uint8 *chpDest, uint32 iSize)
{
	m_iPacketSize = iSize;

	return ReadData(chpDest, iSize);
}

// 읽기 위치에 변경을 주지 핞고 원하는 데이터 위치에서 데이터 읽기.
MyPacketHeader MyMessageBase::GetHeaderData()
{
	MyPacketHeader header;
	FMemory::Memcpy((uint8*)&header, m_chpDataFieldStart, sizeof(MyPacketHeader));
	return header;
}

// 데이터 읽기/쓰기 준비
void MyMessageBase::SeekMessage(ESeekType type)
{
	m_chpReadPos = m_chpWritePos = m_chpDataFieldStart;

	switch (type)
	{
	case ESeekType::Read:
		// 읽기인 경우
		m_chpReadPos	+= sizeof(MyPacketHeader);
		m_iDataSize		= m_iPacketSize - sizeof(MyPacketHeader);		// 데이터 처음 위치로 이동
		break;

	case ESeekType::Write:
		// 쓰기 일 경우
		m_chpWritePos	+= sizeof(MyPacketHeader);
		m_iDataSize		= sizeof(MyPacketHeader);						// 데이터 처음 위치로 이동
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
