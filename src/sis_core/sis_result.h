#ifndef SIS_RESULT_H
#define SIS_RESULT_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#include "sis_core_global.h"
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Types
//
enum class SiSType 
{
	Bool,
	Char,

	Int8,
	Int16,
	Int32,
	Int64,

	UInt8,
	UInt16,
	UInt32,
	UInt64,

	Real32,
	Real64,

	Void,

	Undefined
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Global Methods
//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// abstract class IResult
//
class SIS_CORE_EXPORT IResult
{
public:// Constructor, Destructor
	IResult() = default;

	virtual ~IResult() = default;

public:// Interface Methods
	virtual IResult* Init(byte* pBegin) = 0;
	virtual offset Size() = 0;

	virtual bool ToBool() = 0;
	virtual char ToChar() = 0;

	virtual int8 ToInt8() = 0;
	virtual int16 ToInt16() = 0;
	virtual int32 ToInt32() = 0;
	virtual int64 ToInt64() = 0;

	virtual uint8 ToUInt8() = 0;
	virtual uint16 ToUInt16() = 0;
	virtual uint32 ToUInt32() = 0;
	virtual uint64 ToUInt64() = 0;

	virtual real32 ToReal32() = 0;
	virtual real64 ToReal64() = 0;

	virtual void* ToVoid() = 0;

private:// Contents

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CResult
//
template <typename T>
class CResult : public IResult
{
public:// Constructor, Destructor
	CResult() = default;
	CResult(T tData);
	CResult(byte* pBegin);

	~CResult() = default;

public:// Interface Methods
	IResult* Init(byte* pBegin) override;
	offset Size() override;

	bool ToBool() override;
	char ToChar() override;

	int8 ToInt8() override;
	int16 ToInt16() override;
	int32 ToInt32() override;
	int64 ToInt64() override;

	uint8 ToUInt8() override;
	uint16 ToUInt16() override;
	uint32 ToUInt32() override;
	uint64 ToUInt64() override;

	real32 ToReal32() override;
	real64 ToReal64() override;

	void* ToVoid() override;

public:// Operators
	//template <typename TRight>
	//CResult& operator = (TRight const& other);

private:// Contents
	T m_tData;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////// Implementing Inline Methods //////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CResult
//

// Constructor, Destructor
template <typename T>
CResult<T>::CResult(byte* pBegin)
{
	m_tData = *(T*) (pBegin);
	pBegin += sizeof(T);
}

template <typename T>
CResult<T>::CResult(T tData)
{
	m_tData = tData;
}

// Interface Methods
template <typename T>
IResult* CResult<T>::Init(byte* pBegin)
{
	m_tData = *(T*) (pBegin);

	return &this;
}

template <typename T>
offset CResult<T>::Size()
{
	return sizeof(T);
}


template <typename T>
bool CResult<T>::ToBool()
{
	(bool) (m_tData);
}

template <typename T>
char CResult<T>::ToChar()
{
	(char) (m_tData);
}

template <typename T>
int8 CResult<T>::ToInt8()
{
	(int8) (m_tData);
}

template <typename T>
int16 CResult<T>::ToInt16()
{
	(int16) (m_tData);
}

template <typename T>
int32 CResult<T>::ToInt32()
{
	(int32) (m_tData);
}

template <typename T>
int64 CResult<T>::ToInt64()
{
	(int64) (m_tData);
}

template <typename T>
uint8 CResult<T>::ToUInt8()
{
	(uint8) (m_tData);
}

template <typename T>
uint16 CResult<T>::ToUInt16()
{
	(uint16) (m_tData);
}

template <typename T>
uint32 CResult<T>::ToUInt32()
{
	(uint32) (m_tData);
}


template <typename T>
uint64 CResult<T>::ToUInt64()
{
	(uint64) (m_tData);
}


template <typename T>
real32 CResult<T>::ToReal32()
{
	(real32) (m_tData);
}


template <typename T>
real64 CResult<T>::ToReal64()
{
	(real64) (m_tData);
}


template <typename T>
void* CResult<T>::ToVoid()
{
	(void*) (&m_tData);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SIS_RESULT_H
// end of file
